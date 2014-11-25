
#include "Common.h"

int Extension::GetRed(int x, int y)
{
	COLORREF color = GetColor(x,y);
	int r = GetRValue(color);
	return r;
}

int Extension::GetGreen(int x, int y)
{
	COLORREF color = GetColor(x,y);
	return GetGValue(color);
}

int Extension::GetBlue(int x, int y)
{
	COLORREF color = GetColor(x,y);
	return GetBValue(color);
}

COLORREF Extension::GetColor(int x, int y)
{
	COLORREF color = 0;
	if (x >= 0 && y >= 0)
	{
		try{
			fprh rhPtr = rdPtr->rHo.hoAdRunHeader;
			LPSURFACE ps = WinGetSurface((int)rhPtr->rhIdEditWin);
		
			int w = ps->GetWidth();
			int h = ps->GetHeight();
			if (renderSurf != NULL)
			{
				delete renderSurf;
				renderSurf = NULL;
			}
			LPSURFACE pProto1 = NULL;
			if (GetSurfacePrototype(&pProto1, ps->GetDepth(), ST_MEMORY, SD_DIB))
			{
				renderSurf = new cSurface;
				renderSurf->Create(1, 1, pProto1);
			}

			LPSURFACE pSrcSf = ps;
			cSurface rttSf;
			int nDrv = ps->GetDriver();
			if (x <= ps->GetWidth() && y <= ps->GetHeight())
			{
				if (nDrv == SD_D3D9 || nDrv == SD_D3D8)
				{
					LPSURFACE pProto;
					GetSurfacePrototype(&pProto, ps->GetDepth(), ST_HWA_ROUTEXTURE, nDrv);
					rttSf.Create(1, 1, pProto);
					ps->Blit(rttSf, 0, 0, x, y, 1, 1, BMODE_OPAQUE);
					pSrcSf = &rttSf;
					pSrcSf->Blit(*renderSurf);
					color = renderSurf->GetPixelFast(0, 0);
				}
				else{
					color = ps->GetPixelFast(x, y);
				}
			}
		}
		catch (exception e)
		{
			int i = 0;
		}
	}
	return color;
}
