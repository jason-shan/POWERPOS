VERSION 2.00
Begin Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   990
   ClientLeft      =   1095
   ClientTop       =   1710
   ClientWidth     =   3330
   Height          =   1500
   Left            =   1035
   LinkTopic       =   "Form1"
   ScaleHeight     =   990
   ScaleWidth      =   3330
   Top             =   1260
   Width           =   3450
   Begin CommandButton Command1 
      Caption         =   "Command1"
      Height          =   495
      Left            =   1080
      TabIndex        =   0
      Top             =   240
      Width           =   1215
   End
End
Option Explicit

Sub Command1_Click ()
    Dim req As ylrequest, response As ylresponse
    req.trantype = TRANS_MC_PURCHACE
    req.posnumber = "002"
    req.TransAmount = 1
    req.xsdanjuhao = "123456789012"
    btrstatus = merRemote(req, response)
End Sub

