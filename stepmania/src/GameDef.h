#pragma once
/*
-----------------------------------------------------------------------------
 Class: GameDef

 Desc: Holds information about a particular style of a game (e.g. "single", "double").

 Copyright (c) 2001-2002 by the person(s) listed below.  All rights reserved.
	Chris Danford
-----------------------------------------------------------------------------
*/

#include "Notes.h"
#include "NoteData.h"
#include "GameInput.h"
#include "MenuInput.h"
#include "GameConstantsAndTypes.h"


const int MAX_STYLES_PER_GAME = 10;

enum SkinElement { 
	GRAPHIC_NOTE_COLOR_PART,
	GRAPHIC_NOTE_GRAY_PART,
	GRAPHIC_RECEPTOR,
	GRAPHIC_TAP_EXPLOSION_BRIGHT,
	GRAPHIC_TAP_EXPLOSION_DIM,
	GRAPHIC_HOLD_EXPLOSION,
	NUM_GAME_BUTTON_GRAPHICS	// leave this at the end
};

//
// PrimaryMenuButton and SecondaryMenuButton are used to support using DeviceInputs that only 
// navigate the menus.
// 
// A button being a primary menu button means that this GameButton will generate a the 
// corresponding MenuInput.
// A button being a primary menu button means that this GameButton will generate a the
// corresponding MenuInput IF AND ONLY IF the GameButton corresponding to the pimary input 
// is not mapped.
//
// Example 1:  A user is using a an arcade DDR machine as their controllre.  This machine has 
// MenuLeft, MenuStart, and MenuRight buttons on the cabinet, so they should be used to navigate menus.
// The user will map these DeviceInputs to the GameButtons "MenuLeft (optional)", "MenuStart", and 
// "MenuRight (optional)".
//
// Example 2:  A user is using PlayStation DDR soft pads to play.  His controller don't have dedicated
// DeviceInputs for MenuLeft and MenuRight.  The user maps Up, Down, Left, and Right as normal.
// Since the Left and Right GameButtons have the flag FLAG_SECONDARY_MENU_*, they will function as 
// MenuLeft and MenuRight as long as "MenuLeft (optional)" and "MenuRight (optional)" are not mapped.
//

class StyleDef;

class GameDef
{
public:
	char	m_szName[60];
	char	m_szDescription[60];
	int		m_iNumControllers;
	int		m_iButtonsPerController;
	char	m_szButtonNames[MAX_GAME_BUTTONS][60];	// The name used by the button graphics system.  e.g. "left", "right", "middle C", "snare"
	char	m_szButtonDescriptions[MAX_GAME_BUTTONS][60];	// just a longer name shown in the mapping screen
	GameButton	m_DedicatedMenuButton[NUM_MENU_BUTTONS];
	GameButton	m_SecondaryMenuButton[NUM_MENU_BUTTONS];
	int		m_iDefaultKeyboardKey[MAX_GAME_CONTROLLERS][MAX_GAME_BUTTONS];	// default keyboard keys only have an effect the current game is this game

	GameButton ButtonNameToIndex( const CString &sButtonName )
	{
		for( int i=0; i<m_iButtonsPerController; i++ ) 
			if( stricmp(m_szButtonNames[i], sButtonName) == 0 )
				return i;
		return GAME_BUTTON_INVALID;
	}

	MenuInput GameInputToMenuInput( GameInput GameI );
	void MenuInputToGameInput( MenuInput MenuI, GameInput GameIout[4] );

	// note skin stuff
	void GetSkinNames( CStringArray &asSkinNames );
	bool HasASkinNamed( CString sSkin );
	void AssertSkinsAreComplete();
	void AssertSkinIsComplete( CString sSkin );

	CString GetPathToGraphic( const CString sSkinName, const CString sButtonName, const SkinElement gbg );
	void	GetTapTweenColors( const CString sSkinName, const CString sButtonName, CArray<D3DXCOLOR,D3DXCOLOR> &aTapTweenColorsAddTo );
	void	GetHoldTweenColors( const CString sSkinName, const CString sButtonName, CArray<D3DXCOLOR,D3DXCOLOR> &aHoldTweenColorsAddTo );
	CString ElementToGraphicSuffix( const SkinElement gbg );
};
