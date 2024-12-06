#pragma once
#include <string>
#include <afxwin.h>  // For MFC classes like CDialogEx and CWnd



class CRHBDlg : public CDialogEx
{
public:
    CRHBDlg(CWnd* pParent = nullptr);   // Constructor

    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_RHB_DIALOG };  // Dialog ID
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);  // DDX/DDV support
    virtual BOOL OnInitDialog();  // Initialize dialog

    // Function declarations
    afx_msg void OnBnClickedSaveAndRun();
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();

    DECLARE_MESSAGE_MAP()  // Message map

protected:
    // Member variables
    HICON m_hIcon;
    CString m_authorization;
    CString m_sessionToken;
    CString m_schoolName;
    CString m_unitsToComplete;
    CString m_userId;
    CString m_languageCode;

private:
    void SaveToConstantsJson();  // Custom function to save to JSON
    void RunIndexJs();  // Function to run the JS script
};
