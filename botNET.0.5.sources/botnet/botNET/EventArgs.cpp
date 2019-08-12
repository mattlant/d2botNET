#include "botnet.h"
#include "eventargs.h"
#include "item.h"
#include "game.h"
#include "rosterplayer.h"

namespace botNET
{
    ///////////////////////////////////////////////////////////
    // ItemActionArgs
    ///////////////////////////////////////////////////////////
    ItemActionEventArgs::ItemActionEventArgs( BYTE* packet )
    {
        m_hItem = new botNET::Units::Item((Int32)(((int*)packet)[1]));
        m_nActionType = (ItemActionType)packet[1];

        switch( packet[0] )
        {
            case 0x9C:
                m_nLocation = (ItemLocation)((packet[15] & 0x0000000F) >> 1);
                m_nGridX    = (packet[14] & 0x0000000F) >> 1;
                m_nGridY    = (packet[14] & 0x0000000F) >> 5;
                break;

            case 0x9D:
                m_nLocation = (ItemLocation)((packet[20] & 0x0000000F) >> 1);
                m_nGridX    = (packet[19] & 0x0000000F) >> 1;
                m_nGridY    = (packet[19] & 0x0000000F) >> 5;
                break;
        }

        switch( (int)m_nLocation )
        {
            case 1:
                m_nLocation = ItemLocation::Inventory;
                break;
            case 3:
                m_nLocation = ItemLocation::Ground;
                break;
            case 4:
                m_nLocation = ItemLocation::Cube;
                break;
            case 5:
                m_nLocation = ItemLocation::Stash;
                break;
        }
    }

	botNET::Units::Item* ItemActionEventArgs::get_Item()
    {
        return m_hItem;
    }

    ItemActionType ItemActionEventArgs::get_ActionType(void)
    {
        return m_nActionType;
    }

    ItemLocation ItemActionEventArgs::get_Location(void)
    {
        return m_nLocation;
    }

    int ItemActionEventArgs::get_GridX(void)
    {
        return m_nGridX;
    }

    int ItemActionEventArgs::get_GridY(void)
    {
        return m_nGridY;
    }

    ///////////////////////////////////////////////////////////
	//GameEventArgs
	///////////////////////////////////////////////////////////
	GameEventArgs::GameEventArgs(double gameLength)
	{
		gamelength = gameLength;
	}

	double GameEventArgs::get_GameLength()
	{
		return gamelength;
	}

	///////////////////////////////////////////////////////////
	//ChatLineMessageEventArgs
	///////////////////////////////////////////////////////////
	ChatLineMessageEventArgs::ChatLineMessageEventArgs(String * ChatMsg)
	{
		message = ChatMsg;
		PassMessage = true;
	}

	String * ChatLineMessageEventArgs::get_Message()
	{
		return message;
	}

	///////////////////////////////////////////////////////////
	//KeyClickEventArgs
	///////////////////////////////////////////////////////////
	KeyPressEventArgs::KeyPressEventArgs(KeyPressEventType k, int WParam, int LParam)
	{
		wparam = WParam;
		lparam = LParam;
		windowhandle = Game::Window::Handle;
		PassKey = true;
		type = k;
	}

	KeyPressEventType KeyPressEventArgs::get_Type()
	{
		return type;
	}

	int KeyPressEventArgs::get_WParam()
	{
		return wparam;
	}

	int KeyPressEventArgs::get_LParam()
	{
		return lparam;
	}

	IntPtr KeyPressEventArgs::get_WindowHandle()
	{
		return windowhandle;
	}

	///////////////////////////////////////////////////////////
	//TextChangedEventArgs
	///////////////////////////////////////////////////////////
	TextChangedEventArgs::TextChangedEventArgs(String * newText)
	{
		NewText = newText;
	}



	///////////////////////////////////////////////////////////
	//MouseClickEventArgs
	///////////////////////////////////////////////////////////
	MouseActionEventArgs::MouseActionEventArgs(MouseEventType type, int clickedX, int clickedY)
	{

		this->_point = System::Drawing::Point(clickedX, clickedY);
		etype = type;
		PassClick = true;
	}

	int MouseActionEventArgs::get_ClickX()
	{
		return this->_point.X;
	}

	int MouseActionEventArgs::get_ClickY()
	{
		return this->_point.Y;
	}

	System::Drawing::Point MouseActionEventArgs::get_ClickPoint()
	{
		return this->_point;
	}

	MouseEventType MouseActionEventArgs::get_Type()
	{
		return etype;
	}

}
