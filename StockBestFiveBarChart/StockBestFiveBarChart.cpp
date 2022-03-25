// StockBestFiveBarChart.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
}

void __fastcall TPriceFrame::StringGrid3DrawCell(TObject* Sender, int ACol,
    int ARow, TRect& Rect, TGridDrawState State)
{
    if (g_pQuoteWarehouse == NULL) return;

    //StringGrid3->Canvas->Font->Style = TFontStyles() << fsBold;
    int nVirRow = 7;

    bool bSuspend = false;

    try
    {
        const CStock* pStock = SelectStock();
        if (pStock->IsSuspend())
            bSuspend = true;

        if (pStock->GetMarketNo() == 0x02)
            nVirRow = 9;
    }
    catch (...)
    {
    }

    if (ARow == 0 || ARow == nVirRow)
    {
        StringGrid3->Canvas->Font->Color = clWhite;//clBlack;
        StringGrid3->Canvas->Brush->Color = StringGrid3->FixedColor;//clBtnFace;
        StringGrid3->Canvas->FillRect(Rect);
    }
    else if (ARow > 0 && ARow < nVirRow && ACol == 0)//賣張
    {
        if ((m_cMarketNo != 5) && (m_cMarketNo != 6) && (m_cMarketNo != 7))
        {
            if (bSuspend)
            {
                StringGrid3->Canvas->Font->Color = (TColor)0x00A1A1A1;
            }
            else
            {
                StringGrid3->Canvas->Font->Color = clLime;
                StringGrid3->Canvas->Brush->Color = clBlack;
            }
            StringGrid3->Canvas->FillRect(Rect);
        }
        else
        {
            StringGrid3->Canvas->Font->Color = clLime;
            StringGrid3->Canvas->Brush->Color = clBlack;
            StringGrid3->Canvas->FillRect(Rect);
        }
    }
    else if (ARow > nVirRow && ACol == 1)//買張
    {
        if ((m_cMarketNo != 5) && (m_cMarketNo != 6) && (m_cMarketNo != 7))
        {
            if (bSuspend)
                StringGrid3->Canvas->Font->Color = (TColor)0x00A1A1A1;
            else {
                StringGrid3->Canvas->Font->Color = clRed;
                StringGrid3->Canvas->Brush->Color = clBlack;
            }
            StringGrid3->Canvas->FillRect(Rect);
        }
        else {
            StringGrid3->Canvas->Font->Color = clRed;
            StringGrid3->Canvas->Brush->Color = clBlack;
            StringGrid3->Canvas->FillRect(Rect);
        }
    }
    else
    {
        if (m_cMarketNo == 5 || m_cMarketNo == 7)
        {
            try
            {
                COverseaBest10* pBest10 = NULL;
                if (m_cMarketNo == 5)
                    pBest10 = g_pQuoteWarehouse->GetOSFutureBest10(m_usExchangeID, m_usCommodity);
                else
                    pBest10 = g_pQuoteWarehouse->GetOSOptionBest10(m_usExchangeID, m_usCommodity);

                double dValue = 0.0;

                if (ARow > nVirRow && ACol == 0)//買價
                {
                    if (ARow == nVirRow + 1)
                        dValue = pBest10->GetBuyPrice1();
                    else if (ARow == nVirRow + 2)
                        dValue = pBest10->GetBuyPrice2();
                    else if (ARow == nVirRow + 3)
                        dValue = pBest10->GetBuyPrice3();
                    else if (ARow == nVirRow + 4)
                        dValue = pBest10->GetBuyPrice4();
                    else if (ARow == nVirRow + 5)
                        dValue = pBest10->GetBuyPrice5();
                }
                else if (ARow > 0 && ARow < nVirRow && ACol == 1)//賣價
                {
                    if (ARow == 1)
                        dValue = pBest10->GetSellPrice5();
                    else if (ARow == 2)
                        dValue = pBest10->GetSellPrice4();
                    else if (ARow == 3)
                        dValue = pBest10->GetSellPrice3();
                    else if (ARow == 4)
                        dValue = pBest10->GetSellPrice2();
                    else if (ARow == 5)
                        dValue = pBest10->GetSellPrice1();
                }

                if (m_pForeign)
                {
                    double dRefPrice = m_pForeign->GetRefPrice();

                    if (dRefPrice > dValue)
                        StringGrid3->Canvas->Font->Color = clLime;
                    else if (dRefPrice < dValue)
                        StringGrid3->Canvas->Font->Color = clRed;
                    else
                        StringGrid3->Canvas->Font->Color = clWhite;
                }
            }
            catch (...)
            {
            }
        }
        else if (m_cMarketNo == 6)
        {
            try
            {
                CHKBest5* pBest5 = g_pQuoteWarehouse->GetHKBest5(m_sStockidx);

                double dValue = 0.0;

                if (ARow > nVirRow && ACol == 0)//買價
                {
                    if (ARow == nVirRow + 1)
                        dValue = pBest5->GetBuyPrice1();
                    else if (ARow == nVirRow + 2)
                        dValue = pBest5->GetBuyPrice2();
                    else if (ARow == nVirRow + 3)
                        dValue = pBest5->GetBuyPrice3();
                    else if (ARow == nVirRow + 4)
                        dValue = pBest5->GetBuyPrice4();
                    else if (ARow == nVirRow + 5)
                        dValue = pBest5->GetBuyPrice5();
                }
                else if (ARow > 0 && ARow < nVirRow && ACol == 1)//賣價
                {
                    if (ARow == 1)
                        dValue = pBest5->GetSellPrice5();
                    else if (ARow == 2)
                        dValue = pBest5->GetSellPrice4();
                    else if (ARow == 3)
                        dValue = pBest5->GetSellPrice3();
                    else if (ARow == 4)
                        dValue = pBest5->GetSellPrice2();
                    else if (ARow == 5)
                        dValue = pBest5->GetSellPrice1();
                }

                if (m_pHKStock)
                {
                    double dRefPrice = m_pHKStock->GetRefPrice();

                    if (dRefPrice > dValue)
                        StringGrid3->Canvas->Font->Color = clLime;
                    else if (dRefPrice < dValue)
                        StringGrid3->Canvas->Font->Color = clRed;
                    else
                        StringGrid3->Canvas->Font->Color = clWhite;
                }
            }
            catch (...)
            {
            }
        }
        else if (m_cMarketNo == 9 || m_cMarketNo == 10)
        {
            try
            {
                COSStockBest5* pBest5 = g_pQuoteWarehouse->GetOSStockBest5(m_cMarketNo, m_sStockidx);

                double dValue = 0.0;
                if (ARow > nVirRow && ACol == 0)//買價
                {
                    if (ARow == nVirRow + 1)
                        dValue = pBest5->GetBuyPrice1();
                    else if (ARow == nVirRow + 2)
                        dValue = pBest5->GetBuyPrice2();
                    else if (ARow == nVirRow + 3)
                        dValue = pBest5->GetBuyPrice3();
                    else if (ARow == nVirRow + 4)
                        dValue = pBest5->GetBuyPrice4();
                    else if (ARow == nVirRow + 5)
                        dValue = pBest5->GetBuyPrice5();
                }
                else if (ARow > 0 && ARow < nVirRow && ACol == 1)//賣價
                {
                    if (ARow == 1)
                        dValue = pBest5->GetSellPrice5();
                    else if (ARow == 2)
                        dValue = pBest5->GetSellPrice4();
                    else if (ARow == 3)
                        dValue = pBest5->GetSellPrice3();
                    else if (ARow == 4)
                        dValue = pBest5->GetSellPrice2();
                    else if (ARow == 5)
                        dValue = pBest5->GetSellPrice1();
                }

                if (m_pOSStock)
                {
                    double dRefPrice = m_pOSStock->GetRefPrice();

                    if (dRefPrice > dValue)
                        StringGrid3->Canvas->Font->Color = clLime;
                    else if (dRefPrice < dValue)
                        StringGrid3->Canvas->Font->Color = clRed;
                    else
                        StringGrid3->Canvas->Font->Color = clWhite;
                }
            }
            catch (...)
            {
            }
        }
        else
        {
            try
            {
                const CStock* pStock = g_pQuoteWarehouse->GetStock(m_cMarketNo, m_sStockidx);

                if (StringGrid3->Cells[ACol][ARow] != "")
                {
                    double dUp = RoundTo(pStock->GetUp(), -pStock->GetDecimal());
                    double dDown = RoundTo(pStock->GetDown(), -pStock->GetDecimal());
                    double dYday = RoundTo(pStock->GetYDay(), -pStock->GetDecimal());
                    double dValue = RoundTo(StringGrid3->Cells[ACol][ARow].ToDouble(), -pStock->GetDecimal());

                    if (dValue == dUp)
                    {
                        StringGrid3->Canvas->Font->Color = clWhite;
                        StringGrid3->Canvas->Brush->Color = clRed;
                    }
                    else if (dValue == dDown)
                    {
                        StringGrid3->Canvas->Font->Color = clBlack;
                        StringGrid3->Canvas->Brush->Color = clLime;
                    }
                    else if (dValue > dYday)
                        StringGrid3->Canvas->Font->Color = clRed;
                    else if (dValue < dYday)
                        StringGrid3->Canvas->Font->Color = clLime;
                    else
                        StringGrid3->Canvas->Font->Color = clWhite;

                    if (bSuspend)
                        StringGrid3->Canvas->Font->Color = (TColor)0x00A1A1A1;
                }
            }
            catch (...)
            {
            }
        }
    }

    try
    {
        const CStock* pStock = SelectStock();

        if (pStock->GetMarketNo() == 0x02)
        {
            nVirRow = 9;

            if (ARow == nVirRow - 2 || ARow == StringGrid3->RowCount - 2)
            {
                StringGrid3->Canvas->Font->Color = clWhite;//clBlack;
                StringGrid3->Canvas->Brush->Color = StringGrid3->FixedColor;//clBtnFace;
                StringGrid3->Canvas->FillRect(Rect);
            }
        }
    }
    catch (...)
    {
    }

    if (//(m_cMarketNo == 0x02 || m_cMarketNo == 0x03 ) &&
        StringGrid3->Tag == 1 &&
        StringGrid3->Canvas->Brush->Color == clBlack)
        StringGrid3->Canvas->Brush->Color = (TColor)0x004F334D;

    AnsiString text = StringGrid3->Cells[ACol][ARow];
    int width = StringGrid3->Canvas->TextWidth(StringGrid3->Cells[ACol][ARow]);
    int height = StringGrid3->Canvas->TextHeight(StringGrid3->Cells[ACol][ARow]);

    if (ARow == 0 || ARow == nVirRow)
        StringGrid3->Canvas->TextRect(Rect, (Rect.Left + Rect.Right - width) / 2, (Rect.Top + Rect.Bottom - height) / 2, text);
    else
        StringGrid3->Canvas->TextRect(Rect, Rect.Right - width - 1, (Rect.Top + Rect.Bottom - height) / 2, text);
    //畫線
    if (State.Contains(gdFixed) || ARow == nVirRow)
        StringGrid3->Canvas->Brush->Color = (TColor)0x006A6A6A;
    else
        StringGrid3->Canvas->Brush->Color = StringGrid3->FixedColor;//(TColor)0x00555555;

    TRect RectLine;
    //下
    RectLine.left = Rect.left - 1;
    RectLine.top = Rect.Bottom;
    RectLine.right = Rect.right + 1;
    RectLine.Bottom = Rect.Bottom + 1;
    StringGrid3->Canvas->FillRect(RectLine);
    //右
    RectLine.left = Rect.right;
    RectLine.top = Rect.top;
    RectLine.right = Rect.right + 1;
    RectLine.Bottom = Rect.Bottom;
    StringGrid3->Canvas->FillRect(RectLine);
    //-----------------------------------------------------------------------------------------------
    try
    {
        string strBuyRevisedTotal = "";
        int nMaxWidth = 0;
        double dRate = 0.0;
        double dWidth = 0.0;
        if (ACol == 0 && ARow > 0 && ARow < 6)     //賣張
        {
            //數字寬度
            string strSellTotal = "";
            for (int i = 1; i < 6; i++)      //第一檔到第五檔賣張
            {
                AnsiString strSellPerContent = StringGrid3->Cells[ACol][i];
                int nTextWidth = StringGrid3->Canvas->TextWidth(strSellPerContent);
                if (nTextWidth > nMaxWidth)
                {
                    nMaxWidth = nTextWidth;
                }
            }
            string strSellRevisedTotal = "";
            if ((((StringGrid3->Cells[ACol][ARow]).c_str()) != NULL) &&
                (atoi((StringGrid3->Cells[ACol][ARow]).c_str()) != 0))
            {
                strSellRevisedTotal = (StringGrid3->Cells[ACol][6]).c_str();
                int nFindLeft = strSellRevisedTotal.find("(");
                if (nFindLeft >= 0)
                {
                    strSellRevisedTotal = strSellRevisedTotal.erase(nFindLeft, 1);
                }
                int nFindRight = strSellRevisedTotal.find(")");
                if (nFindRight >= 0)
                {
                    strSellRevisedTotal = strSellRevisedTotal.erase(nFindRight, 1);
                }
                if (atoi((strSellRevisedTotal).c_str()) > 0)
                {
                    dRate = atof((StringGrid3->Cells[ACol][ARow]).c_str()) / atof((strSellRevisedTotal).c_str());
                    dWidth = (Rect.right - Rect.left) * dRate;   // 比例寬度
                }
            }
            Rect.right = Rect.right - nMaxWidth - 1;
            StringGrid3->Canvas->MoveTo(Rect.left, Rect.top + 2);
            int nx1 = Rect.left;                                                                                                                                                                     // (x2,y2)
            int ny1 = (Rect.top + 1);
            int nx2 = Rect.left + dWidth;
            int ny2 = (Rect.Bottom - 1);
            StringGrid3->Canvas->Brush->Color = clLime;
            StringGrid3->Canvas->Brush->Style = bsSolid;
            StringGrid3->Canvas->Rectangle(nx1, ny1, nx2, ny2);

        }
        else if (ACol == 1 && ARow > 9 && ARow < 15 && m_cMarketNo == 2)   //期貨市場買張
        {
            //數字寬度
            for (int i = 10; i < 15; i++)                        //第一檔到第五檔買張
            {
                AnsiString strSellPerContent = StringGrid3->Cells[ACol][i];
                int nTextWidth = StringGrid3->Canvas->TextWidth(strSellPerContent);
                if (nTextWidth > nMaxWidth)
                {
                    nMaxWidth = nTextWidth;
                }
            }
            //判斷買張是否為NULL
            if ((((StringGrid3->Cells[ACol][ARow]).c_str()) != NULL) &&
                (atoi((StringGrid3->Cells[ACol][ARow]).c_str()) != 0))
            {
                strBuyRevisedTotal = (StringGrid3->Cells[ACol][15]).c_str();
                int nFindLeft = strBuyRevisedTotal.find("(");
                if (nFindLeft >= 0)
                {
                    strBuyRevisedTotal = strBuyRevisedTotal.erase(nFindLeft, 1);
                }
                int nFindRight = strBuyRevisedTotal.find(")");
                if (nFindRight >= 0)
                {
                    strBuyRevisedTotal = strBuyRevisedTotal.erase(nFindRight, 1);
                }
                if (atoi((strBuyRevisedTotal).c_str()) > 0)
                {
                    dRate = atof((StringGrid3->Cells[ACol][ARow]).c_str()) / atof((strBuyRevisedTotal).c_str());
                    dWidth = (Rect.right - Rect.left) * dRate;
                }
            }
            //長條圖
            Rect.right = Rect.right - nMaxWidth - 1;
            StringGrid3->Canvas->MoveTo(Rect.left, Rect.top + 1);
            int nx1 = Rect.left;                                                                                                                                                                  // (x2,y2)
            int ny1 = (Rect.top + 1);
            int nx2 = Rect.left + dWidth;
            int ny2 = (Rect.Bottom - 1);
            StringGrid3->Canvas->Brush->Color = clRed;
            StringGrid3->Canvas->Brush->Style = bsSolid;
            StringGrid3->Canvas->Rectangle(nx1, ny1, nx2, ny2);

        }
        else if (ACol == 1 && ARow > 6 && ARow < 13 && m_cMarketNo != 2)   //非期貨市場買張
        {
            //數字寬度
            string strBuyTotal = "";
            for (int i = 8; i < 13; i++)                        //第一檔到第五檔買張
            {
                AnsiString strSellPerContent = StringGrid3->Cells[ACol][i];
                int nTextWidth = StringGrid3->Canvas->TextWidth(strSellPerContent);
                if (nTextWidth > nMaxWidth)
                {
                    nMaxWidth = nTextWidth;
                }
            }
            //判斷買張是否為NULL
            if (((StringGrid3->Cells[ACol][ARow]) != NULL) &&
                (atoi((StringGrid3->Cells[ACol][ARow]).c_str()) != 0))
            {
                strBuyRevisedTotal = (StringGrid3->Cells[ACol][13]).c_str();
                int nFindLeft = strBuyRevisedTotal.find("(");
                if (nFindLeft >= 0)
                {
                    strBuyRevisedTotal = strBuyRevisedTotal.erase(nFindLeft, 1);
                }
                int nFindRight = strBuyRevisedTotal.find(")");
                if (nFindRight >= 0)
                {
                    strBuyRevisedTotal = strBuyRevisedTotal.erase(nFindRight, 1);
                }
                if (atoi((strBuyRevisedTotal).c_str()) > 0)
                {
                    dRate = atof((StringGrid3->Cells[ACol][ARow]).c_str()) / atof((strBuyRevisedTotal).c_str());
                    dWidth = (Rect.right - Rect.left) * dRate;
                }
            }
            //長條圖
            Rect.right = Rect.right - nMaxWidth - 1;
            StringGrid3->Canvas->MoveTo(Rect.left, Rect.top + 1);
            int nx1 = Rect.left;                                                                                                                                                                  // (x2,y2)
            int ny1 = (Rect.top + 1);
            int nx2 = Rect.left + dWidth;
            int ny2 = (Rect.Bottom - 1);
            StringGrid3->Canvas->Brush->Color = clRed;
            StringGrid3->Canvas->Brush->Style = bsSolid;
            StringGrid3->Canvas->Rectangle(nx1, ny1, nx2, ny2);
        }
    }
    catch (Exception& e)
    {
    }

}
//---------------------------------------------------------------------------
