#ifndef D2CONTROL_H
#define D2CONTROL_H

#include "definitions.h"

namespace botNET
{
	namespace OutOfGame
	{

		///<summary>
		/// A D2Control represents a Control on the Diablo II out of game screens
		///</summary>
		public __gc class D2Control
		{
		public:

			///<summary>
			/// Gets all the controls on the current Diablo II Out Of Game SCreen
			///</summary>
			///<returns>A <b>D2Control</b> Array representing all the controls on the current screen</returns>
			///<example><code>D2Control[] controls = D2Control.Get();</code></example>
			static D2Control* Get()[];

			///<summary>
			/// Get all the current screen's controls with the specified text.
			///</summary>
			static D2Control* Get(String* name)[];

			///<summary>
			/// Get all the current screen's controls with the specified text and control type.
			///</summary>
			static D2Control* Get(String* name, ControlType type)[];
			
			///<summary>
			/// Get all the current screen's controls at the specified window coordinates.
			///</summary>
			static D2Control* Get(int x, int y)[];

			///<summary>
			/// Get a control of a given type that is closest to a label control with the given text.
			///</summary>
			static D2Control* GetLabeled(String* label, ControlType type);

			///<summary>
			/// Clicks the control defined by this instance
			///</summary>
			static void doClick(int x, int y, ClickType clicktype);

			///<summary>
			/// Clicks the control defined by this instance
			///</summary>
			void Click();

			///<summary>
			/// Clicks the control defined by this instance at the given screen X and Y coordinates
			///</summary>
			///<param name="X"> The X coordinate to click at</param>
			///<param name="Y"> The Y coordinate to click at</param>
			/////<remarks> This only works in 800x600 </remarks>
			void Click(int X, int Y);

			///<summary>
			/// Gets the Type of the Control
			///</summary>
			///<returns> A ControlType value</returns>
			__property ControlType get_Type();

			///<summary>
			/// Gets a value indicating if the control is enabled
			///</summary>
			__property bool get_Enabled();
			//__property void set_Enabled(bool);

			///<summary>
			/// Gets the X screen coordinate of the control
			///</summary>
			__property int get_X();

			///<summary>
			/// Sets the X screen coordinate of the control
			///</summary>
			__property void set_X(int NewX);

			///<summary>
			/// Gets the Y screen coordinate of the control
			///</summary>
			__property int get_Y();

			///<summary>
			/// Sets the Y screen coordinate of the control
			///</summary>
			__property void set_Y(int NewY);

			///<summary>
			/// Gets the width in pixels of the control
			///</summary>
			__property int get_Width();

			///<summary>
			/// Gets the width in pixels of the control
			///</summary>
			__property int get_Height();

			///<summary>
			/// Gets or sets the text of the control. 
			///</summary>
			///<remarks> Not all controls will actually be able to have their text set. </remarks>
			__property String* get_Text();
			__property void set_Text(String * text);

			///<summary>
			/// Gets the text of the control with colour codes. 
			///</summary>
			///<remarks> Not all controls will actually be able to have their text set. </remarks>
			__property String* get_ColoredText();

		public private:
			D2Control(ButtonAttrib * Control);
			~D2Control(void);
			ButtonAttrib * control;


		};

	}

}

#endif