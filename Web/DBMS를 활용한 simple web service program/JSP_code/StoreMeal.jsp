<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>

    	
   
<!DOCTYPE html>
<html>
<head>
<meta charset="EUC-KR">
<title>주문하기</title>
</head>
<body>

    
	<H2>주문하기</H2>
	
	<FORM ACTION=OrderFinish.jsp>
	
	고객 이름 : <INPUT TYPE="TEXT" NAME="CUSNAME"> <br><br>

	<img src="storemealhamburg.jpg" width="150" height="100">
	<SELECT NAME=HAMBURG>
		<OPTION>트러플머쉬룸X</OPTION>
		<OPTION>통새우스테이크</OPTION>
		<OPTION>와퍼</OPTION>
		<OPTION>콰트로치즈와퍼</OPTION>
		<OPTION>BLT롱치킨</OPTION>
		<OPTION>다이나믹BBQ</OPTION>
		<OPTION>더블치킨맨</OPTION>
		<OPTION>치즈버거</OPTION>
	</SELECT>
	<br><br>
	
	<img src="sidemenu.jpg" width="150" height="100">
	<SELECT NAME=SIDEMENU>
		<OPTION>코울슬로</OPTION>
		<OPTION>치즈스틱</OPTION>
		<OPTION>코코넛쉬림프</OPTION>
		<OPTION>텐더킹</OPTION>
		<OPTION>프렌치프라이</OPTION>
		<OPTION>어니언링</OPTION>
		<OPTION>너겟킹</OPTION>
		<OPTION>콘샐러드</OPTION>
	</SELECT>
	<br><br>
	
	<img src="drink.jpg" width="150" height="100">
	<SELECT NAME=DRINK>
		<OPTION>애플모히또</OPTION>
		<OPTION>베리베리젤리에이드</OPTION>
		<OPTION>애플망고젤리에이드</OPTION>
		<OPTION>아메리카노</OPTION>
		<OPTION>카페라떼</OPTION>
		<OPTION>코카콜라</OPTION>
		<OPTION>스프라이트</OPTION>
		<OPTION>핫초코</OPTION>
	</SELECT>
	<br><br>
		<span style="color:green">주문넣기<INPUT TYPE=SUBMIT VALUE="주문넣기"> </span>
	</FORM>
	
	

</body>
</html>