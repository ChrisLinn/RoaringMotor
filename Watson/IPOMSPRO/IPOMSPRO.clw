; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CIPOMSPRODlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "IPOMSPRO.h"

ClassCount=5
Class1=CIPOMSPROApp
Class2=CIPOMSPRODlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_IPOMSPRO_DIALOG
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Class4=Cscope
Class5=SetupDlg
Resource4=IDD_DIALOG1

[CLS:CIPOMSPROApp]
Type=0
HeaderFile=IPOMSPRO.h
ImplementationFile=IPOMSPRO.cpp
Filter=N

[CLS:CIPOMSPRODlg]
Type=0
HeaderFile=IPOMSPRODlg.h
ImplementationFile=IPOMSPRODlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT2

[CLS:CAboutDlg]
Type=0
HeaderFile=IPOMSPRODlg.h
ImplementationFile=IPOMSPRODlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_IPOMSPRO_DIALOG]
Type=1
Class=CIPOMSPRODlg
ControlCount=28
Control1=IDC_STATIC,button,1342177287
Control2=IDC_EDIT2,edit,1484851328
Control3=IDC_EDIT3,edit,1484851328
Control4=IDC_BUTTON1,button,1342242816
Control5=IDC_STATIC,button,1342177287
Control6=IDC_SCOPE,static,1342181388
Control7=IDC_LEFTSTART,button,1342242816
Control8=IDC_EDIT4,edit,1350631552
Control9=IDC_EDIT5,edit,1350631552
Control10=IDC_EDIT6,edit,1350631552
Control11=IDC_EDIT7,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_RIGHTSTART,button,1342242816
Control14=IDC_EXIT,button,1342242816
Control15=IDC_STATICTSH,static,1342308353
Control16=IDC_STATICTSH2,static,1342308353
Control17=IDC_SETUPCOM,button,1342242816
Control18=IDC_PROGRESS1,msctls_progress32,1342177280
Control19=IDC_LIST1,SysListView32,1350565889
Control20=IDC_BUTIMELEFT,button,1342242816
Control21=IDC_BZUTIMERIGHT,button,1342242816
Control22=IDC_CHECK1,button,1342242819
Control23=IDC_CHECK3,button,1342242819
Control24=IDC_CHECK2,button,1342242819
Control25=IDC_CHECK4,button,1342242819
Control26=IDC_BUTIMEUP,button,1342246656
Control27=IDC_BUTIMEDOWN,button,1342246656
Control28=IDC_MSCOMM1,{648A5600-2C6E-101B-82B6-000000000014},1073807360

[DLG:IDD_DIALOG1]
Type=1
Class=SetupDlg
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COMBO_COM,combobox,1344339971
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO_B,combobox,1344339971
Control5=IDC_STATIC,static,1342308352
Control6=IIDC_COMBO_P,combobox,1344339971
Control7=IDOK,button,1342242816
Control8=IDCANCEL,button,1342242816

[CLS:Cscope]
Type=0
HeaderFile=scope1.h
ImplementationFile=scope1.cpp
BaseClass=CButton
Filter=W

[CLS:SetupDlg]
Type=0
HeaderFile=SetupDlg.h
ImplementationFile=SetupDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

