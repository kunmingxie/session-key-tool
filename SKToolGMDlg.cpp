// SKToolGM.cpp: 实现文件//
#include "stdafx.h"
#include "afxdialogex.h"
#include <time.h>
#include <windows.h>
#include "the scheme of zhang.h"
#include "common_data_head.h"
#include "openssl/sha.h"
#include "openssl/bn.h"
#include "openssl/ec.h"
#include "string.h"
#include<iostream>
#include<sstream>
#include<string>
#pragma comment (lib, "libeay32.lib")
#pragma comment(lib,"ws2_32.lib")
#define new DEBUG_NEW
#define _CRT_SECURE_NO_DEPRECATE
#include "SKToolGM.h"
#include "SKToolGMDlg.h"
using namespace std;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MFCAPPLICATION1_DIALOG, pParent)
	, m_id(_T(""))
	, m_pw(_T(""))
	, sign1(_T(""))
	, m_sks(_T(""))
	, m_sku(_T(""))
	, sign2(_T(""))
	, sign3(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDX_Text(pDX, IDC_EDIT2, m_pw);
	DDX_Text(pDX, IDC_EDIT3, sign1);
	DDX_Text(pDX, IDC_EDIT4, m_sks);
	DDX_Text(pDX, IDC_EDIT6, m_sku);
	DDX_Text(pDX, IDC_EDIT5, sign2);
	DDX_Text(pDX, IDC_EDIT7, sign3);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication1Dlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT7, &CMFCApplication1Dlg::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCApplication1Dlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT3, &CMFCApplication1Dlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CMFCApplication1Dlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT6, &CMFCApplication1Dlg::OnEnChangeEdit6)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication1Dlg::OnBnClickedButton5)
	ON_EN_CHANGE(IDC_EDIT5, &CMFCApplication1Dlg::OnEnChangeEdit5)
	ON_BN_CLICKED(IDC_BUTTON6, &CMFCApplication1Dlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CMFCApplication1Dlg::OnEnChangeEdit1()
{
	UpdateData(TRUE);
	m_id;
	UpdateData(FALSE);
}											//读取输入的id值


void CMFCApplication1Dlg::OnEnChangeEdit7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}




void CMFCApplication1Dlg::OnEnChangeEdit8()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CMFCApplication1Dlg::OnEnChangeEdit2()
{
	UpdateData(TRUE);
	m_pw;
	UpdateData(FALSE);
}																//读取输入的pw值


/*设置全局所用的函数变量*/
char * id = " ";
char * pw = " ";
unsigned char HId[HASH_LEN] = { 0 };
unsigned char VR[HASH_LEN] = { 0 };
unsigned char N[HASH_LEN] = { 0 };
unsigned char R[HASH_LEN] = { 0 };
unsigned char VPw1[HASH_LEN] = { 0 };
unsigned char D[HASH_LEN] = { 0 };
unsigned char Auths[HASH_LEN] = { 0 };
unsigned char ra[HASH_LEN] = { 0 };
unsigned char HId1[HASH_LEN] = { 0 };
unsigned char sks[HASH_LEN] = { 0 };
unsigned char sku[HASH_LEN] = { 1 };


/*点击服务器认证用户后进行的运行的函数*/
void CMFCApplication1Dlg::OnBnClickedButton2()
{

	if (m_id == "" || m_pw == "")
	{
		AfxMessageBox(_T("输入的用户ID密码PW数据不完整，请重新输入！"));
		return;
	}

	int i = 0;																
	SHA256_CTX sha256_ctx;
	unsigned char rb1[HASH_LEN] = { 0 };
	unsigned char R1[HASH_LEN] = { 0 };
	unsigned char ra1[HASH_LEN] = { 0 };
	unsigned char Authu1[HASH_LEN] = { 0 };
	unsigned char Authu[HASH_LEN] = { 0 };
	unsigned char C[HASH_LEN] = { 0 };
	unsigned char r1[HASH_LEN] = { 0 };
	unsigned char h[HASH_LEN] = { 0 };
	unsigned char h1[HASH_LEN] = { 0 };
	unsigned char Us[HASH_LEN] = { 0 };
	unsigned char VPw[HASH_LEN] = { 0 };
	unsigned char VPw11[HASH_LEN] = { 0 };

	srand(time(NULL));
	for (i = 0; i<32; i++)
	{
		ra[i] = (rand() % 10 + '0');						// 生成随机数ra
	}

	/*            USER             */
	memset(h, 0, HASH_LEN);
	for (i = 0; i < HASH_LEN; i++)
	{
		h[i] = pw[i] ^ id[i];
	}
	SHA256_Init(&sha256_ctx);
	SHA256_Update(&sha256_ctx, h, HASH_LEN);
	SHA256_Final(h1, &sha256_ctx);
	for (i = 0; i < HASH_LEN; i++)
	{
		r1[i] = VR[i] ^ h1[i];
	}																//计算r'=VR⊕h(PW⊕ID)

	memset(h, 0, HASH_LEN);
	for (i = 0; i < HASH_LEN; i++)
	{
		h[i] = id[i] ^ r1[i];
	}
	SHA256_Init(&sha256_ctx);
	SHA256_Update(&sha256_ctx, h, HASH_LEN);
	SHA256_Final(HId1, &sha256_ctx);									//计算HId'=h(ID⊕r')


	SHA256_Init(&sha256_ctx);
	SHA256_Update(&sha256_ctx, pw, strlen(pw));
	SHA256_Update(&sha256_ctx, id, strlen(id));
	SHA256_Update(&sha256_ctx, r1, HASH_LEN);
	SHA256_Final(VPw1, &sha256_ctx);									 //计算VPw'=h(PW||ID||r')

	memset(h, 0, HASH_LEN);
	for (i = 0; i < HASH_LEN; i++)
	{
		h[i] = R[i] ^ VPw1[i];
	}
	memset(h1, 0, HASH_LEN);
	SHA256_Init(&sha256_ctx);
	SHA256_Update(&sha256_ctx, h, HASH_LEN);
	SHA256_Final(h1, &sha256_ctx);
	for (i = 0; i < HASH_LEN; i++)
	{
		C[i] = h1[i] ^ ra[i];
	}																		//计算C=h(R⊕VPw')

	memset(h, 0, HASH_LEN);
	for (i = 0; i < HASH_LEN; i++)
	{
		h[i] = ra[i] ^ HId1[i];
	}
	memset(h1, 0, HASH_LEN);
	for (i = 0; i < HASH_LEN; i++)
	{
		h1[i] = h[i] ^ VPw1[i];
	}
	memset(h, 0, HASH_LEN);
	SHA256_Init(&sha256_ctx);
	SHA256_Update(&sha256_ctx, h1, HASH_LEN);
	SHA256_Final(Authu, &sha256_ctx);									//计算Authu=h(ra⊕HId'⊕VPw')

																		/*            SEVER             */
	unsigned char rb[HASH_LEN] = { 0 };
	for (i = 0; i<32; i++)
	{
		rb[i] = (rand() % 10 + '0');
	}																		//生成随机数rb

	memset(h, 0, HASH_LEN);
	SHA256_Init(&sha256_ctx);
	SHA256_Update(&sha256_ctx, str_Sp, HASH_LEN);
	SHA256_Update(&sha256_ctx, HId1, HASH_LEN);
	SHA256_Final(h, &sha256_ctx);
	for (i = 0; i < HASH_LEN; i++)
	{
		VPw11[i] = N[i] ^ h[i];
	}																	//计算VPw''=N⊕h(sp||HId')

	memset(h, 0, HASH_LEN);
	for (i = 0; i < HASH_LEN; i++)
	{
		h[i] = str_Sp[i] ^ VPw11[i];
	}
	SHA256_Init(&sha256_ctx);
	SHA256_Update(&sha256_ctx, h, HASH_LEN);
	SHA256_Final(R1, &sha256_ctx);										//计算R'=h(sp⊕VPw'')

	memset(h, 0, HASH_LEN);
	for (i = 0; i < HASH_LEN; i++)
	{
		h[i] = R1[i] ^ VPw11[i];
	}
	memset(h1, 0, HASH_LEN);
	SHA256_Init(&sha256_ctx);
	SHA256_Update(&sha256_ctx, h, HASH_LEN);
	SHA256_Final(h1, &sha256_ctx);
	for (i = 0; i < HASH_LEN; i++)
	{
		ra1[i] = h1[i] ^ C[i];
	}																	//计算ra'=h(R'⊕VPw'')⊕C

	memset(h, 0, HASH_LEN);
	for (i = 0; i < HASH_LEN; i++)
	{
		h[i] = ra1[i] ^ HId[i];
	}
	memset(h1, 0, HASH_LEN);
	for (i = 0; i < HASH_LEN; i++)
	{
		h1[i] = h[i] ^ VPw11[i];
	}
	memset(h, 0, HASH_LEN);
	SHA256_Init(&sha256_ctx);
	SHA256_Update(&sha256_ctx, h1, HASH_LEN);
	SHA256_Final(Authu1, &sha256_ctx);								//计算 Authu1=h(ra'⊕HId'⊕VPw'')


	for (i = 0; i < HASH_LEN; i++)
	{
		if (Authu[i] != Authu1[i])
		{
			printf("登录阶段认证 Authu != Authu1 失败\n");
			UpdateData(TRUE);
			sign1 = "认证失败";
			UpdateData(FALSE);
			GetDlgItem(IDC_EDIT4)->SetWindowText(_T(""));
			return;
		}
	}
	printf("登录阶段认证 Authu = Authu1 成功\n");						  //check whether the value of Authu is equal to h(ra'⊕HId'⊕VPw'')

	SHA256_Init(&sha256_ctx);
	SHA256_Update(&sha256_ctx, ra1, HASH_LEN);
	SHA256_Update(&sha256_ctx, rb, HASH_LEN);
	SHA256_Update(&sha256_ctx, HId1, HASH_LEN);
	SHA256_Final(sks, &sha256_ctx);									//计算sks=h(ra'||rb ||HId')

	UpdateData(TRUE);
	sign1 = "已获取会话密钥";
	UpdateData(FALSE);

	CString str, tem;
	for (int i = 0; i < 32; i++)
	{
		tem.Format(_T("%02x"), sks[i]);
		str += tem;
	}

	UpdateData(TRUE);
	m_sks = str;
	UpdateData(FALSE);

	memset(h, 0, HASH_LEN);
	SHA256_Init(&sha256_ctx);
	SHA256_Update(&sha256_ctx, R1, HASH_LEN);
	SHA256_Update(&sha256_ctx, VPw11, HASH_LEN);
	SHA256_Final(h, &sha256_ctx);
	for (i = 0; i < HASH_LEN; i++)
	{
		D[i] = h[i] ^ rb[i];
	}																//计算 D=h(R'||VPw'')⊕rb
	SHA256_Init(&sha256_ctx);
	SHA256_Update(&sha256_ctx, sks, HASH_LEN);
	SHA256_Update(&sha256_ctx, D, HASH_LEN);
	SHA256_Final(Auths, &sha256_ctx);								//计算Auths=h( sks||D) 

	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
	}



	//点击用户认证服务器后进行的运行的函数//
void CMFCApplication1Dlg::OnBnClickedButton3()
{

	if (m_id == "" || m_pw == "")
	{
		AfxMessageBox(_T("输入的用户ID密码PW数据不完整，请重新输入！"));
		return;
	}

	DWORD dwid = WideCharToMultiByte(CP_OEMCP, NULL, m_id, -1, NULL, NULL, 0, NULL);
	id = new char[dwid]; WideCharToMultiByte(CP_OEMCP, NULL, m_id, -1, id, dwid, 0, NULL);	//将编辑框读取的数据赋给id

	DWORD dwpw = WideCharToMultiByte(CP_OEMCP, NULL, m_pw, -1, NULL, NULL, 0, NULL);
	pw = new char[dwpw]; WideCharToMultiByte(CP_OEMCP, NULL, m_pw, -1, id, dwpw, 0, NULL);	//将编辑框读取的数据赋给pw

	int i;
	SHA256_CTX sha256_ctx;
	unsigned char rb1[HASH_LEN] = { 0 };
	unsigned char h[HASH_LEN] = { 0 };
	unsigned char Auths1[HASH_LEN] = { 0 };

	/*            USER             */

	memset(h, 0, HASH_LEN);
	SHA256_Init(&sha256_ctx);
	SHA256_Update(&sha256_ctx, R, HASH_LEN);
	SHA256_Update(&sha256_ctx, VPw1, HASH_LEN);
	SHA256_Final(h, &sha256_ctx);
	for (i = 0; i < HASH_LEN; i++)
	{
		rb1[i] = h[i] ^ D[i];
	}																//计算	rb'=h(R||VPw'')⊕D

	SHA256_Init(&sha256_ctx);
	SHA256_Update(&sha256_ctx, ra, HASH_LEN);
	SHA256_Update(&sha256_ctx, rb1, HASH_LEN);
	SHA256_Update(&sha256_ctx, HId1, HASH_LEN);
	SHA256_Final(sku, &sha256_ctx);										//计算 sku=h(ra || rb'|| HId')

	SHA256_Init(&sha256_ctx);
	SHA256_Update(&sha256_ctx, sku, HASH_LEN);
	SHA256_Update(&sha256_ctx, D, HASH_LEN);
	SHA256_Final(Auths1, &sha256_ctx);									//计算 Auths1=h(sku||D)

	for (i = 0; i < HASH_LEN; i++)
	{
		if (Auths[i] != Auths1[i])
		{
			printf("登录阶段认证 Auths != Auths1 失败\n");
			UpdateData(TRUE);
			sign2 = "认证失败";
			UpdateData(FALSE);
			GetDlgItem(IDC_EDIT6)->SetWindowText(_T(""));
			return;
		}
	}
	printf("登录阶段认证 Auths = Auths1 成功\n");							//check whether Auths is equal to h(sku||D)
	printf("登录成功\n");


	UpdateData(TRUE);
	sign2 = "已获取会话密钥";
	UpdateData(FALSE);

	CString str1, tem1;
	for (int i = 0; i < 32; i++)
	{
		tem1.Format(_T("%02x"), sku[i]);
		str1 += tem1;
	}

	UpdateData(TRUE);
	m_sku = str1;
	UpdateData(FALSE);
	int j = 0;
	GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);

																		// TODO: 在此添加控件通知处理程序代码
}


void CMFCApplication1Dlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMFCApplication1Dlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}



void CMFCApplication1Dlg::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


//点击注册后进行的运行的函数//
void CMFCApplication1Dlg::OnBnClickedButton5()
{
	if (m_id == ""|| m_pw =="")
	{
		AfxMessageBox(_T("输入的数据不完整，请重新输入！"));
		return;
	}

	DWORD dwid = WideCharToMultiByte(CP_OEMCP, NULL, m_id, -1, NULL, NULL, 0, NULL);
	id = new char[dwid]; WideCharToMultiByte(CP_OEMCP, NULL, m_id, -1, id, dwid, 0, NULL);	//将编辑框读取的数据赋给id

	DWORD dwpw = WideCharToMultiByte(CP_OEMCP, NULL, m_pw, -1, NULL, NULL, 0, NULL);
	pw = new char[dwpw]; WideCharToMultiByte(CP_OEMCP, NULL, m_pw, -1, pw, dwpw, 0, NULL);	//将编辑框读取的数据赋给id

	SHA256_CTX ctx;
	unsigned char h[HASH_LEN] = { 0 };
	unsigned char h1[HASH_LEN] = { 0 };
	unsigned char r[HASH_LEN] = { 0 };
	unsigned char Us[HASH_LEN] = { 0 };
	unsigned char VPw[HASH_LEN] = { 0 };

	/*           USER             */
	int i;
	srand(time(NULL));
	for (i = 0; i<32; i++)
	{
		r[i] = (rand() % 10 + '0');
	}																			//生成随机数r

	SHA256_Init(&ctx);
	SHA256_Update(&ctx, pw, strlen(pw));
	SHA256_Update(&ctx, id, strlen(id));
	SHA256_Update(&ctx, r, HASH_LEN);
	SHA256_Final(VPw, &ctx);												 //计算VPw=h(PW||ID||r)

	for (i = 0; i < HASH_LEN; i++)
	{
		h[i] = id[i] ^ r[i];
	}
	SHA256_Init(&ctx);
	SHA256_Update(&ctx, h, HASH_LEN);
	SHA256_Final(HId, &ctx);												  //计算HId=h(ID⊕r)

  /*            SEVER             */
	memset(h, 0, HASH_LEN);
	SHA256_Init(&ctx);
	SHA256_Update(&ctx, str_Sp, HASH_LEN);
	SHA256_Update(&ctx, HId, HASH_LEN);
	SHA256_Final(h, &ctx);
	for (i = 0; i < HASH_LEN; i++)
	{
		N[i] = VPw[i] ^ h[i];
	}																        //计算N=VPw⊕h(sp||HId)

	memset(h, 0, HASH_LEN);
	for (i = 0; i < HASH_LEN; i++)
	{
		h[i] = str_Sp[i] ^ VPw[i];
	}
	SHA256_Init(&ctx);
	SHA256_Update(&ctx, h, HASH_LEN);
	SHA256_Final(R, &ctx);													//计算R=h(sp⊕VPw)

	/*            USER             */
	memset(h, 0, HASH_LEN);
	for (i = 0; i < HASH_LEN; i++)
	{
		h[i] = pw[i] ^ id[i];
	}
	SHA256_Init(&ctx);
	SHA256_Update(&ctx, h, HASH_LEN);
	SHA256_Final(h1, &ctx);
	for (i = 0; i < HASH_LEN; i++)
	{
		VR[i] = h1[i] ^ r[i];
	}
	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON3)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON6)->EnableWindow(TRUE);

	AfxMessageBox(_T("注册成功！"));					//如果输入空注册失败，弹出对话框			
}


void CMFCApplication1Dlg::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialog::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

//点击双方密钥匹配后进行运行的函数//
void CMFCApplication1Dlg::OnBnClickedButton6()
{
	int i = 0;
	int j = 0;
	UpdateData(TRUE);
	sign3 = "失败";
	UpdateData(FALSE);								//默认匹配失败
	for (i = 0; i < HASH_LEN; i++)
	{
		if (sks[i] == sku[i])
		{
			j = j++;
		}
	}											  //判断密钥字符串是否相等
	if (j == 32)
	{
		UpdateData(TRUE);
		sign3 = "成功";
		GetDlgItem(IDC_BUTTON6)->EnableWindow(FALSE);
		UpdateData(FALSE);
	}											//显示匹配成功
	// TODO: 在此添加控件通知处理程序代码
}


void CAboutDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
