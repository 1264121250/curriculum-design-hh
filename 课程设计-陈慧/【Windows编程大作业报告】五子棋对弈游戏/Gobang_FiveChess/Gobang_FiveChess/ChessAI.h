#pragma once
#include "ChessCommon.h"

// ����AI�����ٶ��𽥼�����CPUռ�������ߣ�����Ҳ������
// AIFoolish         ��Ȼ������ͣ�����ռ�õ��ڴ��CPU����͵ģ�
// AIPrimary         ռ���ڴ�ͣ�ռ��CPUҲ��
// AIMiddle          �ڴ��CPUռ�þ���
// AIHigh            ռ���ڴ�ͣ�ռ��CPU��

// ����Ĭ�ϻ���Ϊ�׷�
BOOL    AIFoolish (POINT&	 ptPosWhite,	POINT ptPosBlack,	enumChessColor   emChessColor,  const  enumChessColor emChess[][ROWS]);    //AIBlock   // �谭��AI�� 	�����谭���ֳ�5��	�����ϵ�      
BOOL    AIPrimary (POINT &pt ,   enumChessColor emChess[][ROWS]);                // ����AI      
BOOL    AIMiddle  (POINT &pt ,   const  enumChessColor emChess[][ROWS]);         // �м�AI     
BOOL    AIHigh    (POINT &pt ,   enumChessColor emChess[][ROWS]);                // �߼�AI      ����������Сalpha-beta��֦
