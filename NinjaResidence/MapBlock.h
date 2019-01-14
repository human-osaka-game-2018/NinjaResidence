/**
* @file MapBlock.h
* @brief enum BLOCKTYPEの宣言
* @author Kojiro Kawahara
*/
#pragma once

namespace MapBlock
{
	/**
	* @enum BLOCKTYPE
	* ブロック種別
	*/
	enum BLOCKTYPE//CSVのブロックの番号
	{
		NONE,
		WOOD_BLOCK,
		ROCK_BLOCK,
		WOOD_TRACT,
		ROCK_TRACT,
		WOOD_REVERSE_ZONE,
		ROCK_REVERSE_ZONE,
		DESCRIPTION_BOARD,
		DESCRIPTION_BOARD2,
		START_ZONE,
		GOAL_ZONE,
	};
}

