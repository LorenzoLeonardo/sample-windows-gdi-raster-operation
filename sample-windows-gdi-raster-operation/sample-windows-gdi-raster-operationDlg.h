
// sample-windows-gdi-raster-operationDlg.h : header file
//

#pragma once

// CsamplewindowsgdirasteroperationDlg dialog
class CsamplewindowsgdirasteroperationDlg : public CDialogEx {
    // Construction
  public:
    CsamplewindowsgdirasteroperationDlg(CWnd* pParent = nullptr); // standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_SAMPLEWINDOWSGDIRASTEROPERATION_DIALOG };
#endif

  protected:
    virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support

    // Implementation
  protected:
    HICON m_hIcon;
    HBITMAP m_hbmColor = {};
    HBITMAP m_hbmMask = {};
    BOOL m_showTransparent = {};
    CBrush m_brushBackground;

    HBITMAP CreateMonochromeMaskFromBitmap(HBITMAP hbmColor,
                                           COLORREF transparent = RGB(255, 255, 255));
    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
  public:
    afx_msg void OnDestroy();
    afx_msg void OnBnClickedCancel();
    afx_msg void OnBnClickedOk();

  private:
    CButton m_ctrlBtnToggle;

  public:
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
