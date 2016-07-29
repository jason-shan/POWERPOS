Option Explicit
Global btrstatus As Integer

Type ylrequest
    TransAmount As Long
    trantype As Integer
    posnumber As String * 4
    xsdanjuhao As String * 20
    yxsdanjuhao As String * 20
End Type

Type ylresponse
    TransAmount As Double               '金额
    rejcode As String * 4               '返回码
    CardNumber As String * 20           '卡号
    RejCodeExplain As String * 100      '返回码解释
    CardType As Long
End Type
Global Const cdtp_Credit% = 1           '信用卡
Global Const cdtp_Member% = 2           '会员卡
Global Const cdtp_Smart% = 3            '斯玛特卡
Global Const cdtp_WK% = 6               '巍康卡
Global Const cdtp_OKCard% = 5           'OK会员卡
Global Const cdtp_OKPoint% = 7          'OK积点卡
Global Const cdtp_AliPay% = 90          '支付宝

Global Const TRANS_MC_PURCHACE& = 2              '消费
Global Const TRANS_MC_VOID& = 3                  '消费撤销
Global Const TRANS_MC_REPRT& = 16                '重打签购单

Global Const TRANS_MC_INFOR& = 15                '磁卡查询
Global Const TRANS_MC_TUI& = 3                   '退货
Global Const TRANS_MC_ROL& = 14                  '结账

Declare Function unionbank Lib "shums16.dll" (ByVal trantype As Long, ByVal amount As Long, responsedata As Any) As Integer
Declare Function remotePay Lib "shums16.dll" (request As Any, response As Any) As Integer

Function merRemote (req As ylrequest, userdata As ylresponse) As Integer
    Dim s$, tle$
    btrstatus = remotePay(req, userdata)
    If btrstatus <> 0 Then
        s = "调用接口返回错误" + Format$(btrstatus)
    ElseIf userdata.rejcode <> "10" Then
        s = Trim$(userdata.RejCodeExplain)
    Else
        merRemote = True: Exit Function
    End If
    Select Case req.trantype
    Case TRANS_MC_PURCHACE
        tle = "移动支付消费错误"
    Case TRANS_MC_TUI
        tle = "移动支付退货错误"
    End Select
    MsgBox s, mb_ok, tle
    merRemote = False
End Function

