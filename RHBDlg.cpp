#include "pch.h"
#include "RHB.h"
#include "RHBDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <json.hpp>  // Correct for JSON for Modern C++

#include <windows.h>
#include <sstream> 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CRHBDlg::CRHBDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_RHB_DIALOG, pParent)
    , m_authorization(_T(""))
    , m_sessionToken(_T(""))
    , m_schoolName(_T(""))
    , m_unitsToComplete(_T(""))
    , m_userId(_T(""))
    , m_languageCode(_T(""))
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRHBDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_AUTHORIZATION, m_authorization);
    DDX_Text(pDX, IDC_SESSIONTOKEN, m_sessionToken);
    DDX_Text(pDX, IDC_SCHOOLNAME, m_schoolName);
    DDX_Text(pDX, IDC_UNITSTOCOMPLETE, m_unitsToComplete);
    DDX_Text(pDX, IDC_USERID, m_userId);
    DDX_Text(pDX, IDC_LANGUAGECODE, m_languageCode);
}

BEGIN_MESSAGE_MAP(CRHBDlg, CDialogEx)
    ON_BN_CLICKED(IDC_SAVE_AND_RUN, &CRHBDlg::OnBnClickedSaveAndRun)
    ON_WM_PAINT()           // Mapping OnPaint
    ON_WM_QUERYDRAGICON()   // Mapping OnQueryDragIcon
END_MESSAGE_MAP()



BOOL CRHBDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);


    return TRUE;
}

void CRHBDlg::SaveToConstantsJson()
{
    UpdateData(TRUE);









    // Convert CString to std::string
    std::string authorization(CT2A(m_authorization.GetString()));
    std::string sessionToken(CT2A(m_sessionToken.GetString()));
    std::string schoolName(CT2A(m_schoolName.GetString()));
    std::string unitsToComplete(CT2A(m_unitsToComplete.GetString()));
    std::string userId(CT2A(m_userId.GetString()));
    std::string languageCode(CT2A(m_languageCode.GetString()));

    // Prepare JSON data (using nlohmann::json)
    nlohmann::json root;
    root["person"] = "User";
    root["authorization"] = authorization;
    root["sessionToken"] = sessionToken;
    root["schoolName"] = schoolName;
    root["unitsToComplete"] = nlohmann::json::array();  // Initialize as an empty array

    // Parsing the comma-separated units and append them as integers
    std::istringstream ss(unitsToComplete);
    std::string unit;
    while (std::getline(ss, unit, ',')) {
        root["unitsToComplete"].push_back(std::stoi(unit));  // Convert string to int and append
    }

    root["userId"] = userId;
    root["languageCode"] = languageCode;

    // Write to constants.json
    std::ofstream file("constants.json");
    file << root.dump(4);  // Pretty-print with 4 spaces indentation
    file.close();
}

void CRHBDlg::RunIndexJs()
{
    // Run the Node.js script
    ShellExecute(nullptr, _T("open"), _T("cmd.exe"), _T("/c node index.js"), nullptr, SW_HIDE);
}

void CRHBDlg::OnBnClickedSaveAndRun()
{
    SaveToConstantsJson();
    RunIndexJs();
    AfxMessageBox(_T("Done But Dont Close The Software Yet Azb"));
}

void CRHBDlg::OnPaint()
{
    if (IsIconic()) {
        CPaintDC dc(this);
        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
        dc.DrawIcon(0, 0, m_hIcon);
    }
    else {
        CDialogEx::OnPaint();
    }
}

HCURSOR CRHBDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}
