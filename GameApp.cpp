#include <ClanLib/core.h>
#include <ClanLib/application.h>
#include <ClanLib/display.h>

#ifdef USE_SDL
#include <ClanLib/sdl.h>
#else
#include <ClanLib/gl.h>
#endif

#include "GraphicNode.h"
#include "PlayNode.h"
#include "GameResources.h"
#include "MouseEvent.h"

class GameApp : public CL_ClanApplication
{
public:
	virtual int main(int argc, char **argv)
	{
		// Create a console window for text-output if not available
		CL_ConsoleWindow console("Console");
		console.redirect_stdio();
		
		quit = false;

		try
		{
			CL_SetupCore setup_core;
			CL_SetupDisplay setup_display;

#ifdef USE_SDL
			CL_SetupSDL setup_sdl;
#else
			CL_SetupGL setup_gl;
#endif
		
			CL_DisplayWindow window("Laberinto", 1280, 800);
			CL_Slot slot_quit = window.sig_window_close().connect(this, &GameApp::OnWindowClose);

			// Inicializamos el juego
			InitializeGame();

			CL_Point prevMousePos;
			prevMousePos.x = CL_Mouse::get_x();
			prevMousePos.y = CL_Mouse::get_y();

			bool prevMouseLeftDown = false;

			while (!quit){
				CL_Display::clear(CL_Color(0,0,56));

				if (!currentNode){
					throw CL_Error("Fatal error: currentNode is null");
				}

				// Generamos los eventos de raton
				CL_Point mousePos;
				mousePos.x = CL_Mouse::get_x();
				mousePos.y = CL_Mouse::get_y();

				bool mouseLeftDown = CL_Mouse::get_keycode(CL_MOUSE_LEFT);

				// MouseOver
				{					
					MouseEvent mouseEvent;
					mouseEvent.SetMousePosition(mousePos);
				
					currentNode->OnMouseOver(mouseEvent);
				}

				// MouseDown
				{
					if ( mouseLeftDown && !prevMouseLeftDown )
					{
						MouseEvent mouseEvent;
						mouseEvent.SetMousePosition(mousePos);
						mouseEvent.SetKey(CL_MOUSE_LEFT);

						currentNode->OnMouseDown(mouseEvent);
					}
				}

				prevMousePos = mousePos;
				prevMouseLeftDown = mouseLeftDown;

				// Update & Draw

				currentNode->Update();
				currentNode->Draw(CL_Rect(0,0,CL_Display::get_width(), CL_Display::get_height()));

				CL_Display::flip();
				CL_System::keep_alive(10);

				if ( CL_Keyboard::get_keycode(CL_KEY_ESCAPE) ){
					quit = true;
				}
			}
		}
		catch(CL_Error error)
		{
			std::cout << "Exception caught : " << error.message.c_str() << std::endl;			
			console.display_close_message();

			return -1;
		}
		catch(std::exception exc)
		{
			std::cout << "Exception caught : " << exc.what() << std::endl;
			console.display_close_message();

			return -1;
		}
		catch(...)
		{
			// Unknow error
			std::cout << "Exception caught" << std::endl;
			console.display_close_message();

			return -1;
		}

		return 0;
	}

	GraphicNode * GetCurrentNode()
	{
		return currentNode;
	}

	

private:
	bool quit;
	GraphicNode *currentNode;

	void OnWindowClose()
	{
		quit = true;
	}

	void InitializeGame()
	{
		currentNode = new PlayNode(1);
		GameResources::Instance().SetPlayNode((PlayNode *)currentNode);
	}
} gameInstance;
			
