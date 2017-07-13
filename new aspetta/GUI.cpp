/*
Rest In Peace ApocalypseCheats
*/

#include "GUI.h"
#include "Menu.h"
#include "RenderManager.h"
#include "MetaInfo.h"

#include <algorithm>
#include "tinyxml2.h"
#include "Controls.h"

CGUI GUI;

CGUI::CGUI()
{

}
#define UI_CURSORSIZE       12
#define UI_CURSORFILL       Color(255,255,255)
#define UI_CURSOROUTLINE    Color(20,20,20,140)

#define UI_WIN_TOPHEIGHT	26
#define UI_WIN_TITLEHEIGHT	0

#define UI_TAB_WIDTH		150
#define UI_TAB_HEIGHT		32

#define UI_WIN_CLOSE_X		20
#define UI_WIN_CLOSE_Y      6

#define UI_CHK_SIZE			16

#define COL_WHITE           Color(255, 100, 50)
#define UI_COL_MAIN         Color(231, 183, 92, 255)
#define UI_COL_MAINE        Color(0, 204, 0, 255)
#define UI_COL_MAINDARK     Color(113, 236, 159, 255)
#define UI_COL_FADEMAIN     Color(27, 206, 94, 40)
#define UI_COL_SHADOW		Color(0, 0, 0, 255)
#define UI_COL_CLIENTBACK   Color(238, 0, 50, 255)
#define UI_COL_TABSEPERATOR Color(229, 229, 229, 255)
#define UI_COL_TABTEXT      Color(235, 235, 235, 255)
#define UI_COL_GROUPOUTLINE Color(222, 100, 150, 255)// Draws all windows 
void CGUI::Draw()
{
	bool ShouldDrawCursor = false;

	for (auto window : Windows)
	{
		if (window->m_bIsOpen)
		{
			ShouldDrawCursor = true;
			DrawWindow(window);
		}

	}

	if (ShouldDrawCursor)
	{
		Render::Clear(Mouse.x + 1, Mouse.y, 1, 17, Color(3, 6, 26, 255));
		for (int i = 0; i < 11; i++)
			Render::Clear(Mouse.x + 2 + i, Mouse.y + 1 + i, 1, 1, Color(3, 6, 26, 255));
		Render::Clear(Mouse.x + 8, Mouse.y + 12, 5, 1, Color(3, 6, 26, 255));
		Render::Clear(Mouse.x + 8, Mouse.y + 13, 1, 1, Color(3, 6, 26, 255));
		Render::Clear(Mouse.x + 9, Mouse.y + 14, 1, 2, Color(3, 6, 26, 255));
		Render::Clear(Mouse.x + 10, Mouse.y + 16, 1, 2, Color(3, 6, 26, 255));
		Render::Clear(Mouse.x + 8, Mouse.y + 18, 2, 1, Color(3, 6, 26, 255));
		Render::Clear(Mouse.x + 7, Mouse.y + 16, 1, 2, Color(3, 6, 26, 255));
		Render::Clear(Mouse.x + 6, Mouse.y + 14, 1, 2, Color(3, 6, 26, 255));
		Render::Clear(Mouse.x + 5, Mouse.y + 13, 1, 1, Color(3, 6, 26, 255));
		Render::Clear(Mouse.x + 4, Mouse.y + 14, 1, 1, Color(3, 6, 26, 255));
		Render::Clear(Mouse.x + 3, Mouse.y + 15, 1, 1, Color(3, 6, 26, 255));
		Render::Clear(Mouse.x + 2, Mouse.y + 16, 1, 1, Color(3, 6, 26, 255));
		for (int i = 0; i < 4; i++)
			Render::Clear(Mouse.x + 2 + i, Mouse.y + 2 + i, 1, 14 - (i * 2), Color(37 - (i * 4), 137 - (i * 4), 255 - (i * 4), 255));
		Render::Clear(Mouse.x + 6, Mouse.y + 6, 1, 8, UI_COL_MAIN);
		Render::Clear(Mouse.x + 7, Mouse.y + 7, 1, 9, UI_COL_MAIN);
		for (int i = 0; i < 4; i++)
			Render::Clear(Mouse.x + 8 + i, Mouse.y + 8 + i, 1, 4 - i, Color(37 - (i * 4), 137 - (i * 4), 255 - (i * 4), 255));
		Render::Clear(Mouse.x + 8, Mouse.y + 14, 1, 4, UI_COL_MAIN);
		Render::Clear(Mouse.x + 9, Mouse.y + 16, 1, 2, UI_COL_MAIN);
	}
}

// Handle all input etc
void CGUI::Update()
{
	//Key Array
	std::copy(keys, keys + 255, oldKeys);
	for (int x = 0; x < 255; x++) {
		keys[x] = static_cast<bool>(GetAsyncKeyState(x));
	}

	// Mouse Location
	POINT mp; GetCursorPos(&mp);
	ScreenToClient(GetForegroundWindow(), &mp);
	Mouse.x = mp.x; Mouse.y = mp.y;
	//Interfaces::Surface->SurfaceGetCursorPos(Mouse.x, Mouse.y);

	RECT Screen = Render::GetViewport();

	// Window Binds
	for (auto bind : WindowBinds)
	{
		if (GetKeyPress(bind.first) && bind.second != nullptr)
		{
			bind.second->Toggle();
		}
	}

	// Stop dragging
	if (IsDraggingWindow && !GetKeyState(VK_LBUTTON))
	{
		IsDraggingWindow = false;
		DraggingWindow = nullptr;
	}

	// If we are in the proccess of dragging a window
	if (IsDraggingWindow && GetKeyState(VK_LBUTTON) && !GetKeyPress(VK_LBUTTON))
	{
		if (DraggingWindow)
		{
			DraggingWindow->m_x = Mouse.x - DragOffsetX;
			DraggingWindow->m_y = Mouse.y - DragOffsetY;
		}
	}

	// Process some windows
	for (auto window : Windows)
	{
		if (window->m_bIsOpen)
		{
			// Used to tell the widget processing that there could be a click
			bool bCheckWidgetClicks = false;

			// If the user clicks inside the window
			if (GetKeyPress(VK_LBUTTON))
			{
				bCheckWidgetClicks = true;

				if (IsMouseInRegion(window->m_y, window->m_x + window->m_iWidth, window->m_y + window->m_iHeight, window->m_x))
				{
					// Close Button
					if (IsMouseInRegion(window->m_y, window->m_x + window->m_iWidth, window->m_y + UI_WIN_CLOSE_X, window->m_x + window->m_iWidth - UI_WIN_CLOSE_X))
					{
						window->Toggle();
					}
					else
						// User is selecting a new tab
						if (IsMouseInRegion(window->GetTabArea()))
						{

							bCheckWidgetClicks = true;

							int iTab = 0;
							int TabCount = window->Tabs.size();
							if (TabCount) // If there are some tabs
							{
								int TabCount = window->Tabs.size();
								//RECT TabArea = { window->m_x, window->m_y + UI_WIN_TOPHEIGHT + UI_WIN_TITLEHEIGHT + (i*TabSize) , window->m_iWidth - window->m_iHeight, TabSize };
								int TabSize = (window->m_iWidth - UI_TAB_WIDTH - UI_WIN_TITLEHEIGHT - 214) / TabCount;;
								int Dist = Mouse.y - (window->m_y + UI_WIN_TITLEHEIGHT + UI_WIN_TOPHEIGHT);
								if (Dist < (TabSize*TabCount))
								{
									while (Dist > TabSize)
									{
										if (Dist > TabSize)
										{
											iTab++;
											Dist -= TabSize;
										}
										if (iTab == (TabCount - 1))
										{
											break;
										}
									}
									window->SelectedTab = window->Tabs[iTab];

									// Loose focus on the control
									bCheckWidgetClicks = false;
									window->IsFocusingControl = false;
									window->FocusedControl = nullptr;
								}
							}

						}
					// Is it inside the client area?
						else if (IsMouseInRegion(window->GetClientArea()))
						{
							bCheckWidgetClicks = true;
						}
						else
						{
							// Must be in the around the title or side of the window
							// So we assume the user is trying to drag the window
							IsDraggingWindow = true;
							DraggingWindow = window;
							DragOffsetX = Mouse.x - window->m_x;
							DragOffsetY = Mouse.y - window->m_y;

							// Loose focus on the control
							window->IsFocusingControl = false;
							window->FocusedControl = nullptr;
						}
				}
				else
				{
					// Loose focus on the control
					window->IsFocusingControl = false;
					window->FocusedControl = nullptr;
				}
			}

			// Controls 
			if (window->SelectedTab != nullptr)
			{
				// Focused widget
				bool SkipWidget = false;
				CControl* SkipMe = nullptr;

				// this window is focusing on a widget??
				if (window->IsFocusingControl)
				{
					if (window->FocusedControl != nullptr)
					{
						// We've processed it once, skip it later
						SkipWidget = true;
						SkipMe = window->FocusedControl;

						POINT cAbs = window->FocusedControl->GetAbsolutePos();
						RECT controlRect = { cAbs.x, cAbs.y, window->FocusedControl->m_iWidth, window->FocusedControl->m_iHeight };
						window->FocusedControl->OnUpdate();

						if (window->FocusedControl->Flag(UIFlags::UI_Clickable) && IsMouseInRegion(controlRect) && bCheckWidgetClicks)
						{
							window->FocusedControl->OnClick();

							// If it gets clicked we loose focus
							window->IsFocusingControl = false;
							window->FocusedControl = nullptr;
							bCheckWidgetClicks = false;
						}
					}
				}

				// Itterate over the rest of the control
				for (auto control : window->SelectedTab->Controls)
				{
					if (control != nullptr)
					{
						if (SkipWidget && SkipMe == control)
							continue;

						control->parent = window;

						POINT cAbs = control->GetAbsolutePos();
						RECT controlRect = { cAbs.x, cAbs.y, control->m_iWidth, control->m_iHeight };
						control->OnUpdate();

						if (control->Flag(UIFlags::UI_Clickable) && IsMouseInRegion(controlRect) && bCheckWidgetClicks)
						{
							control->OnClick();
							bCheckWidgetClicks = false;

							// Change of focus
							if (control->Flag(UIFlags::UI_Focusable))
							{
								window->IsFocusingControl = true;
								window->FocusedControl = control;
							}
							else
							{
								window->IsFocusingControl = false;
								window->FocusedControl = nullptr;
							}

						}
					}
				}

				// We must have clicked whitespace
				if (bCheckWidgetClicks)
				{
					// Loose focus on the control
					window->IsFocusingControl = false;
					window->FocusedControl = nullptr;
				}
			}
		}
	}
}

// Returns 
bool CGUI::GetKeyPress(unsigned int key)
{
	if (keys[key] == true && oldKeys[key] == false)
		return true;
	else
		return false;
}

bool CGUI::GetKeyState(unsigned int key)
{
	return keys[key];
}

bool CGUI::IsMouseInRegion(int y, int x2, int y2, int x)
{
	if (Mouse.x > x && Mouse.y > y && Mouse.x < x2 && Mouse.y < y2)
		return true;
	else
		return false;
}

bool CGUI::IsMouseInRegion(RECT region)
{
	return IsMouseInRegion(region.top, region.left + region.right, region.top + region.bottom, region.left);
}

POINT CGUI::GetMouse()
{
	return Mouse;
}

bool CGUI::DrawWindow(CWindow* window)
{
	RECT TextSize = Render::GetTextSize(Render::Fonts::MenuBold, window->Title.c_str());
	int TextX = window->m_x + (window->m_iWidth / 2) - (TextSize.left / 2);
	Render::Clear(window->m_x, window->m_y, window->m_iWidth, window->m_iHeight, Color(25, 25, 25, 255));
	Render::Clear(window->m_x, window->m_y + 2 + 15, window->m_iWidth, 8, UI_COL_MAIN);
	Render::Text(TextX - 26, window->m_y + 1, Color(255, 255, 255, 100), Render::Fonts::MenuBold, "");
	Render::Text(TextX + 26, window->m_y + 1, UI_COL_TABTEXT, Render::Fonts::MenuBold,"Aspetta | Dev build");

	// Tabs
	int TabCount = window->Tabs.size();
	int TabSize = (window->m_iWidth - UI_TAB_WIDTH - UI_WIN_TITLEHEIGHT - 214) / TabCount;
	if (TabCount) // If there are some tabs
	{
		for (int i = 0; i < TabCount; i++)
		{
			RECT TabArea = { window->m_x, window->m_y + UI_WIN_TOPHEIGHT + UI_WIN_TITLEHEIGHT + (i*TabSize) , window->m_iWidth - window->m_iHeight - 200, TabSize };
			CTab *tab = window->Tabs[i];

			Render::Clear(TabArea.left, TabArea.top, UI_TAB_WIDTH, 1, Color(0, 0, 0, 255));
			Render::Clear(TabArea.left, TabArea.top + 1, UI_TAB_WIDTH, 1, Color(48, 48, 48, 255));
			Color txtColor = UI_COL_TABSEPERATOR;

			if (window->SelectedTab == tab)
			{
				Render::Clear(window->m_x, window->m_y + UI_WIN_TOPHEIGHT + UI_WIN_TITLEHEIGHT + (i*TabSize) + 2, UI_TAB_WIDTH, TabSize - 2, Color(20, 20, 20, 255));
				txtColor = UI_COL_MAIN;
			}
			else if (IsMouseInRegion(TabArea))
			{
				// Hover
				txtColor = Color(90, 90, 90, 200);
			}

			Render::Text(TabArea.left + 50 - UI_WIN_TOPHEIGHT - UI_WIN_TITLEHEIGHT + 5, TabArea.top + 50 - UI_WIN_TOPHEIGHT - UI_WIN_TITLEHEIGHT + 5, txtColor, Render::Fonts::Tabs, tab->Title.c_str());
		}
	}
	//Window Outline
	Render::Outline(window->m_x - 1, window->m_y - 1, window->m_iWidth + 2, window->m_iHeight + 2, UI_COL_SHADOW);
	Render::Outline(window->m_x - 2, window->m_y - 2, window->m_iWidth + 4, window->m_iHeight + 4, Color(60, 60, 60, 255));
	Render::Outline(window->m_x - 3, window->m_y - 3, window->m_iWidth + 6, window->m_iHeight + 6, Color(40, 40, 40, 255));
	Render::Outline(window->m_x - 4, window->m_y - 4, window->m_iWidth + 8, window->m_iHeight + 8, Color(40, 40, 40, 255));
	Render::Outline(window->m_x - 5, window->m_y - 5, window->m_iWidth + 10, window->m_iHeight + 10, Color(40, 40, 40, 255));
	Render::Outline(window->m_x - 6, window->m_y - 6, window->m_iWidth + 12, window->m_iHeight + 12, Color(60, 60, 60, 255));
	Render::Outline(window->m_x - 7, window->m_y - 7, window->m_iWidth + 14, window->m_iHeight + 14, Color(31, 31, 31, 255));
	

	// Controls 
	if (window->SelectedTab != nullptr)
	{
		// Focused widget
		bool SkipWidget = false;
		CControl* SkipMe = nullptr;

		// this window is focusing on a widget??
		if (window->IsFocusingControl)
		{
			if (window->FocusedControl != nullptr)
			{
				// We need to draw it last, so skip it in the regular loop
				SkipWidget = true;
				SkipMe = window->FocusedControl;
			}
		}


		// Itterate over all the other controls
		for (auto control : window->SelectedTab->Controls)
		{
			if (SkipWidget && SkipMe == control)
				continue;

			if (control != nullptr && control->Flag(UIFlags::UI_Drawable))
			{
				POINT cAbs = control->GetAbsolutePos();
				RECT controlRect = { cAbs.x, cAbs.y, control->m_iWidth, control->m_iHeight };
				bool hover = false;
				if (IsMouseInRegion(controlRect))
				{
					hover = true;
				}
				control->Draw(hover);
			}
		}

		// Draw the skipped widget last
		if (SkipWidget)
		{
			auto control = window->FocusedControl;

			if (control != nullptr && control->Flag(UIFlags::UI_Drawable))
			{
				POINT cAbs = control->GetAbsolutePos();
				RECT controlRect = { cAbs.x, cAbs.y, control->m_iWidth, control->m_iHeight };
				bool hover = false;
				if (IsMouseInRegion(controlRect))
				{
					hover = true;
				}
				control->Draw(hover);
			}
		}

	}


	return true;
}

void CGUI::RegisterWindow(CWindow* window)
{
	Windows.push_back(window);

	// Resorting to put groupboxes at the start
	for (auto tab : window->Tabs)
	{
		for (auto control : tab->Controls)
		{
			if (control->Flag(UIFlags::UI_RenderFirst))
			{
				CControl * c = control;
				tab->Controls.erase(std::remove(tab->Controls.begin(), tab->Controls.end(), control), tab->Controls.end());
				tab->Controls.insert(tab->Controls.begin(), control);
			}
		}
	}
}

void CGUI::BindWindow(CWindow* window, unsigned char Key)
{
	if (window)
		WindowBinds[Key] = window;
	else
		WindowBinds.erase(Key);
}

void CGUI::SaveWindowState(CWindow* window, std::string Filename)
{
	// Create a whole new document and we'll just save over top of the old one
	tinyxml2::XMLDocument Doc;

	// Root Element is called "AC"
	tinyxml2::XMLElement *Root = Doc.NewElement("AC");
	Doc.LinkEndChild(Root);

	Utilities::Log("Saving Window %s", window->Title.c_str());

	// If the window has some tabs..
	if (Root && window->Tabs.size() > 0)
	{
		for (auto Tab : window->Tabs)
		{
			// Add a new section for this tab
			tinyxml2::XMLElement *TabElement = Doc.NewElement(Tab->Title.c_str());
			Root->LinkEndChild(TabElement);

			Utilities::Log("Saving Tab %s", Tab->Title.c_str());

			// Now we itterate the controls this tab contains
			if (TabElement && Tab->Controls.size() > 0)
			{
				for (auto Control : Tab->Controls)
				{
					// If the control is ok to be saved
					if (Control && Control->Flag(UIFlags::UI_SaveFile) && Control->FileIdentifier.length() > 1 && Control->FileControlType)
					{
						// Create an element for the control
						tinyxml2::XMLElement *ControlElement = Doc.NewElement(Control->FileIdentifier.c_str());
						TabElement->LinkEndChild(ControlElement);

						Utilities::Log("Saving control %s", Control->FileIdentifier.c_str());

						if (!ControlElement)
						{
							Utilities::Log("Errorino :("); // s0 cute
							return;
						}

						CCheckBox* cbx = nullptr;
						CComboBox* cbo = nullptr;
						CKeyBind* key = nullptr;
						CSlider* sld = nullptr;

						// Figure out what kind of control and data this is
						switch (Control->FileControlType)
						{
						case UIControlTypes::UIC_CheckBox:
							cbx = (CCheckBox*)Control;
							ControlElement->SetText(cbx->GetState());
							break;
						case UIControlTypes::UIC_ComboBox:
							cbo = (CComboBox*)Control;
							ControlElement->SetText(cbo->GetIndex());
							break;
						case UIControlTypes::UIC_KeyBind:
							key = (CKeyBind*)Control;
							ControlElement->SetText(key->GetKey());
							break;
						case UIControlTypes::UIC_Slider:
							sld = (CSlider*)Control;
							ControlElement->SetText(sld->GetValue());
							break;
						}
					}
				}
			}
		}
	}

	//Save the file
	if (Doc.SaveFile(Filename.c_str()) != tinyxml2::XML_NO_ERROR)
	{
		MessageBox(NULL, "Failed To Save Config File!", "Aspetta", MB_OK);
	}

}

void CGUI::LoadWindowState(std::string Filename, CWindow* window)
{
	// Lets load our meme
	tinyxml2::XMLDocument Doc;
	if (Doc.LoadFile(Filename.c_str()) == tinyxml2::XML_NO_ERROR)
	{
		tinyxml2::XMLElement *Root = Doc.RootElement();

		// The root "AC" element
		if (Root)
		{
			// If the window has some tabs..
			if (Root && window->Tabs.size() > 0)
			{
				for (auto Tab : window->Tabs)
				{
					// We find the corresponding element for this tab
					tinyxml2::XMLElement *TabElement = Root->FirstChildElement(Tab->Title.c_str());
					if (TabElement)
					{
						// Now we itterate the controls this tab contains
						if (TabElement && Tab->Controls.size() > 0)
						{
							for (auto Control : Tab->Controls)
							{
								// If the control is ok to be saved
								if (Control && Control->Flag(UIFlags::UI_SaveFile) && Control->FileIdentifier.length() > 1 && Control->FileControlType)
								{
									// Get the controls element
									tinyxml2::XMLElement *ControlElement = TabElement->FirstChildElement(Control->FileIdentifier.c_str());

									if (ControlElement)
									{
										CCheckBox* cbx = nullptr;
										CComboBox* cbo = nullptr;
										CKeyBind* key = nullptr;
										CSlider* sld = nullptr;

										// Figure out what kind of control and data this is
										switch (Control->FileControlType)
										{
										case UIControlTypes::UIC_CheckBox:
											cbx = (CCheckBox*)Control;
											cbx->SetState(ControlElement->GetText()[0] == '1' ? true : false);
											break;
										case UIControlTypes::UIC_ComboBox:
											cbo = (CComboBox*)Control;
											cbo->SelectIndex(atoi(ControlElement->GetText()));
											break;
										case UIControlTypes::UIC_KeyBind:
											key = (CKeyBind*)Control;
											key->SetKey(atoi(ControlElement->GetText()));
											break;
										case UIControlTypes::UIC_Slider:
											sld = (CSlider*)Control;
											sld->SetValue(atof(ControlElement->GetText()));
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}