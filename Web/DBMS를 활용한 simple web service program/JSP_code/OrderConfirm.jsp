<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
    <%@ page import = "java.sql.*" %>
<!DOCTYPE html>
<html>
<head>
<meta charset="EUC-KR">
<title>고객을 위한 주문 확인</title>
</head>
<body>
	<h3>주문을 받아주세요</h3>
	<%
  		 Connection conn=null;
    	 Statement stmt = null;
    	 
    	 PreparedStatement pstmt = null;
    	 
    	 ResultSet rs = null;
		 String driver = "oracle.jdbc.driver.OracleDriver";
		 String url = "jdbc:oracle:thin:@localhost:1521:orcl";
 		 
	    	try{
	    	    Class.forName(driver);
	    	    conn=DriverManager.getConnection(url,"system","1234qwer"); //자신의 아이디와 비밀번호
	    	   
	    	
	    	    String query="SELECT * FROM ORDERSHEET";
	    	   stmt = conn.createStatement();
	    
	    	   rs = stmt.executeQuery(query);
	    
    %>
    
    <table border="1" >
    <tr>
    	<td>고객이름</td>
    	<td>햄버거</td>
    	<td>사이드메뉴</td>
    	<td>음료</td>
    	<td>가격</td>
    	
    	<td>주문 받기</td>
    </tr>
    
    
    <%
    	while(rs.next()){
    %>
    <tr>
    <td><%=rs.getString("CUSTOMERNAME") %></td>
    <td><%=rs.getString(2) %></td>
    <td><%=rs.getString(3) %></td>
    <td><%=rs.getString(4) %></td>
    <td><%=rs.getString(5) %></td>
    
    <td>
    <A href="TakeoutOrder.jsp?cusname=<%=rs.getString("CUSTOMERNAME") %>">받기</A>
    </td>
    </tr>
    <%
    	}
    %></table>
    
    <%
    	rs.close();
    	stmt.close();
    	conn.close();
    	
	    }catch(Exception e){
	    	    e.printStackTrace();
	    }
    %>
    
    
    
</body>
</html>