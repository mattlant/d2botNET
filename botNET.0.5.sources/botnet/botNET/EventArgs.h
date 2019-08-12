#ifndef EVENTARGS_H
#define EVENTARGS_H


namespace botNET
{
    ///////////////////////////////////////////////////////////
    // Forward declarations
    ///////////////////////////////////////////////////////////
	namespace Units
	{
	   __gc public class Item;
	   __gc public class RosterPlayer;
	}

    ///////////////////////////////////////////////////////////
    // ItemActionArgs
    ///////////////////////////////////////////////////////////
   __value	public enum	ItemActionType
   {
        AddNew              = 0,
        PickupFromGround    = 1,
        DropToGround        = 2,
        UNKNOWN1            = 3,
        AddToContainer      = 4,
        RemoveFromContainer = 5,
        PutOnBody           = 6,
        UKNOWN2             = 7,
        RemoveFromBody      = 8,
        SwapBodyItem        = 9,
        AddQuantity         = 10,
        NewItemForSale      = 11,
        UNKNOWN3            = 12,
        UNKNOWN4            = 13,
        PutInBelt           = 14,
        RemoveFromBelt      = 15,
        SwapInBelt          = 16,
        UNKNOWN5            = 17,
        UNKNOWN6            = 18,
        ItemInSocket        = 19,
        UNKNOWN7            = 20,
        UpdateStats         = 21,
        UNKNOWN8            = 22,
        SwapWeapon          = 23
   };

    __gc public class ItemActionEventArgs : public EventArgs
    {
        public:
            ItemActionEventArgs( BYTE* packet );

			__property botNET::Units::Item*            get_Item(void);
            __property ItemActionType   get_ActionType(void);
            __property botNET::ItemLocation     get_Location(void);
            __property int              get_GridX(void);
            __property int              get_GridY(void);

        private:
			botNET::Units::Item*	m_hItem;
            ItemActionType			m_nActionType;
			botNET::ItemLocation			m_nLocation;
            int						m_nGridX;
            int						m_nGridY;
    };

	///////////////////////////////////////////////////////////
	//GameEventArgs
	///////////////////////////////////////////////////////////
	__gc public class GameEventArgs : public EventArgs
	{
		public:
			GameEventArgs(double gameLength);

			__property double get_GameLength(void);

		private:
			double gamelength;
	};

	///////////////////////////////////////////////////////////
	//ChatLineMessageEventArgs
	///////////////////////////////////////////////////////////
	__gc public class ChatLineMessageEventArgs : public EventArgs
	{
		public:
			ChatLineMessageEventArgs(String * ChatMsg);

			__property String * get_Message(void);
			bool PassMessage;

		private:
			String * message;
	};

	///////////////////////////////////////////////////////////
	//KeyClickEventArgs
	///////////////////////////////////////////////////////////
	__gc public class KeyPressEventArgs : public EventArgs
	{
		public:
			KeyPressEventArgs(KeyPressEventType k, int WParam, int LParam);

			__property KeyPressEventType get_Type();
			__property int get_WParam(void);
			__property int get_LParam(void);
			__property IntPtr get_WindowHandle(void);
			bool PassKey;

		private:
			KeyPressEventType type;
			int wparam;
			int lparam;
			IntPtr windowhandle;
	};

		///////////////////////////////////////////////////////////
		//ScreenHookTextChangedEventArgs
		///////////////////////////////////////////////////////////
		__gc public class TextChangedEventArgs : public EventArgs
		{
			public:
				TextChangedEventArgs(String * newText);

				String * NewText;

			private:
		};

	///////////////////////////////////////////////////////////
	//MouseClickEventArgs
	///////////////////////////////////////////////////////////
	__gc public class MouseActionEventArgs : public EventArgs
	{
		public:
			MouseActionEventArgs(MouseEventType type, int clickedX, int clickedY);

			__property int get_ClickX();
			__property int get_ClickY();
			__property System::Drawing::Point get_ClickPoint();
			__property MouseEventType get_Type();
			bool PassClick;

		public private:
			System::Drawing::Point _point;
			MouseEventType etype;
	};



}

#endif