<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>

    	
   
<!DOCTYPE html>
<html>
<head>
<meta charset="EUC-KR">
<title>�ֹ��ϱ�</title>
</head>
<body>

    
	<H2>�ֹ��ϱ�</H2>
	
	<FORM ACTION=OrderFinish.jsp>
	
	�� �̸� : <INPUT TYPE="TEXT" NAME="CUSNAME"> <br><br>

	<img src="storemealhamburg.jpg" width="150" height="100">
	<SELECT NAME=HAMBURG>
		<OPTION>Ʈ���øӽ���X</OPTION>
		<OPTION>����콺����ũ</OPTION>
		<OPTION>����</OPTION>
		<OPTION>��Ʈ��ġ�����</OPTION>
		<OPTION>BLT��ġŲ</OPTION>
		<OPTION>���̳���BBQ</OPTION>
		<OPTION>����ġŲ��</OPTION>
		<OPTION>ġ�����</OPTION>
	</SELECT>
	<br><br>
	
	<img src="sidemenu.jpg" width="150" height="100">
	<SELECT NAME=SIDEMENU>
		<OPTION>�ڿｽ��</OPTION>
		<OPTION>ġ�ƽ</OPTION>
		<OPTION>���ڳӽ�����</OPTION>
		<OPTION>�ٴ�ŷ</OPTION>
		<OPTION>����ġ������</OPTION>
		<OPTION>��Ͼ�</OPTION>
		<OPTION>�ʰ�ŷ</OPTION>
		<OPTION>�ܻ�����</OPTION>
	</SELECT>
	<br><br>
	
	<img src="drink.jpg" width="150" height="100">
	<SELECT NAME=DRINK>
		<OPTION>���ø�����</OPTION>
		<OPTION>���������������̵�</OPTION>
		<OPTION>���ø����������̵�</OPTION>
		<OPTION>�Ƹ޸�ī��</OPTION>
		<OPTION>ī���</OPTION>
		<OPTION>��ī�ݶ�</OPTION>
		<OPTION>��������Ʈ</OPTION>
		<OPTION>������</OPTION>
	</SELECT>
	<br><br>
		<span style="color:green">�ֹ��ֱ�<INPUT TYPE=SUBMIT VALUE="�ֹ��ֱ�"> </span>
	</FORM>
	
	

</body>
</html>