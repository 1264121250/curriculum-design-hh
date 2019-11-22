#pragma once

//�����
class CChessDraw
{
public:
	CChessDraw(void);
	~CChessDraw(void);

	void    InitBoard(CRect	rect, UINT	uiRows, UINT	uiCols, UINT	uiBoardWidth, UINT	uiPieceRadius);

	void	SetDC(CDC*	pDC);
	void	DrawBackground();							            // ������
	void	DrawBoard();										    // ������
	BOOL	DrawPiece(CPoint	pt,	BOOL	bBlack);				// ������		
	BOOL	DrawPiece(UINT	uiX,	UINT	uiY,	BOOL	bBlack);// ������		
	void	DrawPieceCur(CPoint	pt);								// ����ǰ�����Ӽ��ϱ��
	void	DrawPieceCur(UINT	uiX,	UINT	uiY);				// ����ǰ�����Ӽ��ϱ��

	CRect	GetRectBoard();	// ��ȡ��������	
	BOOL	GetCoordinateWithPoint(CPoint&	pt,	UINT*	puiX = NULL,	UINT*	puiY = NULL);	// ��֪pt����ȡ���������(puiX,	puiY)	
	BOOL	GetPointWithCoordinate(CPoint&	pt,	UINT	uiX ,	UINT	uiY);                   // ��֪���������(puiX,	puiY)����ȡpt

//	void	    SetColorBK(COLORREF crBegin, COLORREF crEnd, BOOL bVertical = FALSE);		    // ���ñ�����ɫ
//	void	    SetColorBoard(COLORREF cr);		// ����������ɫ
//	void	    SetColorPiece(COLORREF cr);		// ����������ɫ

private:
	CDC*		m_pDC;					// ��ͼDC�����ں�����Ӧ�ó��򴰿ڵĿͻ������л�ͼ
	CRect		m_rcBK;					// ��������	
	CRect		m_rcBoard;				// ��������	
	//һ��CRect�������ڶ�λ���ε����ϽǺ����½ǵ�ĳ�Ա������

	UINT		m_uiBoardCols;			// ���̵�����		// �������С���һ���࣬������(������)���ܲ�һ��
	UINT		m_uiBoardRows;		    // ���̵�����
	UINT		m_uiPieceRadius;		// ���Ӱ뾶
	UINT		m_uiBoardWidth;		    // ÿһ�����̵ı߳�(�����θ���)

	COLORREF	m_crBKBegin;			// ����ɫ��ʼ��
	COLORREF	m_crBKEnd;				// ��β��
	COLORREF	m_crBoard;				// ������������ɫ

	void		DrawSpecialPoints();	// ��ָ���ĵ㣬���������е���Ԫ��5����	����ÿ����Ĺ��򶼲�һ��������赥���޸�
};

