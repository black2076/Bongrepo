<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
    <%!
    int hamburg_price, sidemenu_price, drink_price, total_price = 0;
    %>
<!DOCTYPE html>
<html>
<head>
<meta charset="EUC-KR">
<title>주문확인 및 금액</title>
</head>
<body>
	<h3>주문확인 및 금액</h3>
	
	<%
		String cusname = request.getParameter("CUSNAME");
		out.println("안녕하세요.  " + cusname + "님 주문을 확인해주세요<br><br>");
		
		String hamburg = request.getParameter("HAMBURG"); 
		
		
		if( hamburg.equals("트러플머쉬룸X") )
			hamburg_price = 2500;
		else if(hamburg.equals("통새우스테이크"))
			hamburg_price = 2700;
		else if(hamburg.equals("와퍼"))
			hamburg_price = 1500;
		else if(hamburg.equals("콰트로치즈와퍼"))
			hamburg_price = 1700;
		else if(hamburg.equals("BLT롱치킨"))
			hamburg_price = 2000;
		else if(hamburg.equals("다이나믹BBQ"))
			hamburg_price = 2300;
		else if(hamburg.equals("더블치킨맨"))
			hamburg_price = 1900;
		else 
			hamburg_price = 1300;
		
		out.println("주문하신 햄버거는 " + hamburg + "입니다<br>");
	%>
	
	<%
		String sidemenu = request.getParameter("SIDEMENU");
		
		if( sidemenu.equals("코울슬로") )
			sidemenu_price = 900;
		else if(hamburg.equals("치즈스틱"))
			sidemenu_price = 900;
		else if(hamburg.equals("코코넛쉬림프"))
			sidemenu_price = 1100;
		else if(hamburg.equals("텐더킹"))
			sidemenu_price = 1000;
		else if(hamburg.equals("프렌치프라이"))
			sidemenu_price = 800;
		else if(hamburg.equals("어니언링"))
			sidemenu_price = 700;
		else if(hamburg.equals("너겟킹"))
			sidemenu_price = 800;
		else 
			sidemenu_price = 600;
		
		out.println("주문하신 사이트메뉴는 " + sidemenu + "입니다<br>");
	%>
	
	<%
		String drink = request.getParameter("DRINK");
		
		if( drink.equals("애플모히또") )
			drink_price = 600;
		else if(drink.equals("베리베리젤리에이드"))
			drink_price = 600;
		else if(drink.equals("애플망고젤리에이드"))
			drink_price = 600;
		else if(drink.equals("아메리카노"))
			drink_price = 500;
		else if(drink.equals("카페라떼"))
			drink_price = 500;
		else if(drink.equals("코카콜라"))
			drink_price = 400;
		else if(drink.equals("스프라이트"))
			drink_price = 400;
		else 
			drink_price = 300;
		
		out.println("주문하신 음료는 " + drink + "입니다<br>");			
	%>
	
	<%
		total_price = (hamburg_price + sidemenu_price + drink_price);
		out.println("주문하신 가격은 총 " + total_price + "입니다<br><br><br>");
	%>
	
	<%
		session.setAttribute("CUSNAME", cusname);
		session.setAttribute("HAMBURG", hamburg);
		session.setAttribute("SIDEMENU", sidemenu);
		session.setAttribute("DRINK", drink);
		session.setAttribute("TOTALPRICE",total_price);
	%>
	
	<FORM ACTION=FinishOrder.jsp>
		<span style="color:red">주문끝<INPUT TYPE=SUBMIT VALUE="주문끝"> </span>
	</FORM>
	
	
</body>
</html>