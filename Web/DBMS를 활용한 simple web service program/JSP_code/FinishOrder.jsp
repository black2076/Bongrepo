<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
 
 <%@ page import="java.sql.*" %>  
    
    <%
    	String cusname = (String) session.getAttribute("CUSNAME");
    	String hamburg = (String) session.getAttribute("HAMBURG");
   	 	String sidemenu = (String) session.getAttribute("SIDEMENU");
   	 	String drink = (String) session.getAttribute("DRINK");
  	 	int totalprice = (Integer) session.getAttribute("TOTALPRICE");
    %>
    
    <%
  		 Connection conn=null;
    	 PreparedStatement pstmt = null;
		 String driver = "oracle.jdbc.driver.OracleDriver";
		 String url = "jdbc:oracle:thin:@localhost:1521:orcl";
 		
	    	try{
	    	    Class.forName(driver);
	    	    conn=DriverManager.getConnection(url,"system","1234qwer"); //�ڽ��� ���̵�� ��й�ȣ
	    	   
	    	    String sql = "insert into ORDERSHEET values(?,?,?,?,?)";
	    	    pstmt = conn.prepareStatement(sql);
	    	    pstmt.setString(1,cusname);
	    	    pstmt.setString(2,hamburg);
	    	    pstmt.setString(3,sidemenu);
	    	    pstmt.setString(4,drink);
	    	    pstmt.setInt(5,totalprice);
	    	    pstmt.executeUpdate();
	    	}catch(Exception e){
	    	    e.printStackTrace();
	    	}
	    	
	    	session.invalidate();
    %>
<!DOCTYPE html>
<html>
<head>
<meta charset="EUC-KR">
<title>�ֹ� �Ϸ�</title>
</head>
<body>
	<h2>�ֹ��� �Ϸ�Ǿ����ϴ�.</h2> <br><br>
	<font size = 4>��ø� ��ٷ��ּ���</font>
</body>
</html>