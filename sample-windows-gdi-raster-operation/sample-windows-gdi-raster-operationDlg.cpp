
// sample-windows-gdi-raster-operationDlg.cpp : implementation file
//
#include "pch.h"

#include "afxdialogex.h"
#include "framework.h"
#include "sample-windows-gdi-raster-operation.h"
#include "sample-windows-gdi-raster-operationDlg.h"

#ifdef _DEBUG
#    define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx {
  public:
    CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

  protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

    // Implementation
  protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX) {}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CsamplewindowsgdirasteroperationDlg dialog

CsamplewindowsgdirasteroperationDlg::CsamplewindowsgdirasteroperationDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_SAMPLEWINDOWSGDIRASTEROPERATION_DIALOG, pParent) {
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsamplewindowsgdirasteroperationDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDOK, m_ctrlBtnToggle);
}

BEGIN_MESSAGE_MAP(CsamplewindowsgdirasteroperationDlg, CDialogEx)
ON_WM_SYSCOMMAND()
ON_WM_PAINT()
ON_WM_QUERYDRAGICON()
ON_WM_DESTROY()
ON_BN_CLICKED(IDCANCEL, &CsamplewindowsgdirasteroperationDlg::OnBnClickedCancel)
ON_BN_CLICKED(IDOK, &CsamplewindowsgdirasteroperationDlg::OnBnClickedOk)
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CsamplewindowsgdirasteroperationDlg message handlers

BOOL CsamplewindowsgdirasteroperationDlg::OnInitDialog() {
    CDialogEx::OnInitDialog();

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr) {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty()) {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);  // Set big icon
    SetIcon(m_hIcon, FALSE); // Set small icon

    // TODO: Add extra initialization here
    m_hbmColor =
        (HBITMAP)LoadImage(NULL, _T("google_logo_color.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    m_hbmMask = CreateMonochromeMaskFromBitmap(m_hbmColor);

    m_brushBackground.CreateSolidBrush(RGB(13, 71, 161));
    return TRUE; // return TRUE  unless you set the focus to a control
}

void CsamplewindowsgdirasteroperationDlg::OnSysCommand(UINT nID, LPARAM lParam) {
    if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    } else {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CsamplewindowsgdirasteroperationDlg::OnPaint() {
    CPaintDC dc(this);

    if (!m_hbmColor || !m_hbmMask)
        return;

    BITMAP bm;
    GetObject(m_hbmColor, sizeof(BITMAP), &bm);
    int w = bm.bmWidth;
    int h = bm.bmHeight;

    HDC hdcColor = CreateCompatibleDC(dc);
    HDC hdcMask = CreateCompatibleDC(dc);

    HBITMAP oldColor = (HBITMAP)SelectObject(hdcColor, m_hbmColor);
    HBITMAP oldMask = (HBITMAP)SelectObject(hdcMask, m_hbmMask);

    // Left: Original image
    BitBlt(dc, 10, 10, w, h, hdcColor, 0, 0, SRCCOPY);

    // Center: Mask (just for comparison/debug)
    BitBlt(dc, 30 + w, 10, w, h, hdcMask, 0, 0, SRCCOPY);

    // Right: Transparent result (after applying mask)
    if (m_showTransparent) {
        // First, use the mask with SRCAND to clear the areas that should be transparent (black in
        // the mask)
        BitBlt(dc, 50 + 2 * w, 10, w, h, hdcMask, 0, 0, SRCPAINT);

        // Then, use SRCPAINT to combine the image (colored bitmap) with the mask result
        // (transparent parts)
        BitBlt(dc, 50 + 2 * w, 10, w, h, hdcColor, 0, 0, SRCAND);
    }

    SelectObject(hdcColor, oldColor);
    SelectObject(hdcMask, oldMask);
    DeleteDC(hdcColor);
    DeleteDC(hdcMask);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CsamplewindowsgdirasteroperationDlg::OnQueryDragIcon() {
    return static_cast<HCURSOR>(m_hIcon);
}

void CsamplewindowsgdirasteroperationDlg::OnDestroy() {
    CDialogEx::OnDestroy();

    if (m_hbmColor)
        DeleteObject(m_hbmColor);
    if (m_hbmMask)
        DeleteObject(m_hbmMask);
    m_brushBackground.DeleteObject();
}

void CsamplewindowsgdirasteroperationDlg::OnBnClickedCancel() {
    // TODO: Add your control notification handler code here
    CDialogEx::OnCancel();
}

void CsamplewindowsgdirasteroperationDlg::OnBnClickedOk() {
    // TODO: Add your control notification handler code here
    if (m_showTransparent) {
        m_showTransparent = FALSE;
        m_ctrlBtnToggle.SetWindowTextW(_T("Show Output"));
    } else {
        m_showTransparent = TRUE;
        m_ctrlBtnToggle.SetWindowTextW(_T("Reset"));
    }
    Invalidate(); // Force repaint
}

HBRUSH CsamplewindowsgdirasteroperationDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) {
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

    // Set background color for the dialog itself
    if (nCtlColor == CTLCOLOR_DLG) {
        pDC->SetBkMode(TRANSPARENT);
        return m_brushBackground;
    }

    return hbr;
}

COLORREF InvertColor(COLORREF color) {
    BYTE r = GetRValue(color);
    BYTE g = GetGValue(color);
    BYTE b = GetBValue(color);

    // Invert each component
    return RGB(255 - r, 255 - g, 255 - b);
}

HBITMAP CsamplewindowsgdirasteroperationDlg::CreateMonochromeMaskFromBitmap(HBITMAP hbmColor,
                                                                            COLORREF transparent) {

    if (!hbmColor)
        return NULL;

    BITMAP bm = {};
    GetObject(hbmColor, sizeof(bm), &bm);

    // Create DCs
    HDC hdcScreen = ::GetDC(NULL);
    HDC hdcColor = CreateCompatibleDC(hdcScreen);
    HDC hdcMask = CreateCompatibleDC(hdcScreen);

    // Create monochrome bitmap (1-bit, black and white)
    HBITMAP hbmMask = CreateBitmap(bm.bmWidth, bm.bmHeight, 1, 1, NULL);

    // Select bitmaps
    HBITMAP oldColor = (HBITMAP)SelectObject(hdcColor, hbmColor);
    HBITMAP oldMask = (HBITMAP)SelectObject(hdcMask, hbmMask);

    // Set the background color to black, so black pixels become black in the mask
    SetBkColor(hdcColor, transparent);

    // Loop through each pixel and check its color value
    for (int y = 0; y < bm.bmHeight; ++y) {
        for (int x = 0; x < bm.bmWidth; ++x) {
            COLORREF pixelColor = GetPixel(hdcColor, x, y);
            // If the pixel is not black, set it to white in the mask
            if (pixelColor == transparent) {
                SetPixel(hdcMask, x, y, InvertColor(transparent)); // Black (transparent)
            } else {
                SetPixel(hdcMask, x, y, transparent); // White (opaque)
            }
        }
    }

    // Cleanup
    SelectObject(hdcColor, oldColor);
    SelectObject(hdcMask, oldMask);
    DeleteDC(hdcColor);
    DeleteDC(hdcMask);
    ::ReleaseDC(NULL, hdcScreen);

    return hbmMask;
}