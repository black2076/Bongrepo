<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
    <%!
    int hamburg_price, sidemenu_price, drink_price, total_price = 0;
    %>
<!DOCTYPE html>
<html>
<head>
<meta charset="EUC-KR">
<title>�ֹ�Ȯ�� �� �ݾ�</title>
</head>
<body>
	<h3>�ֹ�Ȯ�� �� �ݾ�</h3>
	
	<%
		String cusname = request.getParameter("CUSNAME");
		out.println("�ȳ��ϼ���.  " + cusname + "�� �ֹ��� Ȯ�����ּ���<br><br>");
		
		String hamburg = request.getParameter("HAMBURG"); 
		
		
		if( hamburg.equals("Ʈ���øӽ���X") )
			hamburg_price = 2500;
		else if(hamburg.equals("����콺����ũ"))
			hamburg_price = 2700;
		else if(hamburg.equals("����"))
			hamburg_price = 1500;
		else if(hamburg.equals("��Ʈ��ġ�����"))
			hamburg_price = 1700;
		else if(hamburg.equals("BLT��ġŲ"))
			hamburg_price = 2000;
		else if(hamburg.equals("���̳���BBQ"))
			hamburg_price = 2300;
		else if(hamburg.equals("����ġŲ��"))
			hamburg_price = 1900;
		else 
			hamburg_price = 1300;
		
		out.println("�ֹ��Ͻ� �ܹ��Ŵ� " + hamburg + "�Դϴ�<br>");
	%>
	
	<%
		String sidemenu = request.getParameter("SIDEMENU");
		
		if( sidemenu.equals("�ڿｽ��") )
			sidemenu_price = 900;
		else if(hamburg.equals("ġ�ƽ"))
			sidemenu_price = 900;
		else if(hamburg.equals("���ڳӽ�����"))
			sidemenu_price = 1100;
		else if(hamburg.equals("�ٴ�ŷ"))
			sidemenu_price = 1000;
		else if(hamburg.equals("����ġ������"))
			sidemenu_price = 800;
		else if(hamburg.equals("��Ͼ�"))
			sidemenu_price = 700;
		else if(hamburg.equals("�ʰ�ŷ"))
			sidemenu_price = 800;
		else 
			sidemenu_price = 600;
		
		out.println("�ֹ��Ͻ� ����Ʈ�޴��� " + sidemenu + "�Դϴ�<br>");
	%>
	
	<%
		String drink = request.getParameter("DRINK");
		
		if( drink.equals("���ø�����") )
			drink_price = 600;
		else if(drink.equals("���������������̵�"))
			drink_price = 600;
		else if(drink.equals("���ø����������̵�"))
			drink_price = 600;
		else if(drink.equals("�Ƹ޸�ī��"))
			drink_price = 500;
		else if(drink.equals("ī���"))
			drink_price = 500;
		else if(drink.equals("��ī�ݶ�"))
			drink_price = 400;
		else if(drink.equals("��������Ʈ"))
			drink_price = 400;
		else 
			drink_price = 300;
		
		out.println("�ֹ��Ͻ� ����� " + drink + "�Դϴ�<br>");			
	%>
	
	<%
		total_price = (hamburg_price + sidemenu_price + drink_price);
		out.println("�ֹ��Ͻ� ������ �� " + total_price + "�Դϴ�<br><br><br>");
	%>
	
	<%
		session.setAttribute("CUSNAME", cusname);
		session.setAttribute("HAMBURG", hamburg);
		session.setAttribute("SIDEMENU", sidemenu);
		session.setAttribute("DRINK", drink);
		session.setAttribute("TOTALPRICE",total_price);
	%>
	
	<FORM ACTION=FinishOrder.jsp>
		<span style="color:red">�ֹ���<INPUT TYPE=SUBMIT VALUE="�ֹ���"> </span>
	</FORM>
	
	
</body>
</html>