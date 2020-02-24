<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">



<!-- ==================================================================== -->
<xsl:template match="/">
<HTML>
<HEAD>
<TITLE>Test Report</TITLE>
<STYLE>
TABLE				{ font-family:'Arial'; font-size:12pt; font-weight:normal; color:#000000; background-color:#FFFFFF; }
TH					{ font-family:'Arial'; font-size:12pt; font-weight:bold;   color:#FFFFFF; background-color:#404080; }
TD					{ font-family:'Arial'; font-size:12pt; font-weight:normal; color:#000000; background-color:#FFFFFF; }
TR.check			{ font-family:'Arial'; font-size:12pt; font-weight:normal; color:#000000; background-color:#FFFFFF; }
TD.check			{ font-family:'Arial'; font-size:12pt; font-weight:normal; color:#000000; background-color:#FFFFFF; }
H1					{ font-family:'Arial';                 font-weight:normal; color:#000000; border-style:solid; border-width:0px; border-bottom-width:3px; border-bottom-color:#404080; }
H2					{ font-family:'Arial';                 font-weight:normal; color:#000000; border-style:solid; border-width:0px; border-bottom-width:2px; border-bottom-color:#404080; }
H3					{ font-family:'Arial';                 font-weight:normal; color:#000000; border-style:solid; border-width:0px; border-bottom-width:1px; border-bottom-color:#404080; margin-bottom:8px; }
H4					{ font-family:'Arial';                 font-weight:normal; color:#000000; border-style:solid; border-width:0px; border-bottom-width:1px; border-bottom-color:#404080; margin-bottom:8px; }
H5					{ font-family:'Arial';                 font-weight:normal; color:#000000; border-style:solid; border-width:0px; border-bottom-width:1px; border-bottom-color:#404080; margin-bottom:8px; }
H6					{ font-family:'Arial';                 font-weight:normal; color:#000000; border-style:solid; border-width:0px; border-bottom-width:1px; border-bottom-color:#404080; margin-bottom:8px; }
SPAN.good			{ font-family:'Arial'; font-size:12pt; font-weight:normal; color:#008080;                           }
SPAN.critical		{ font-family:'Arial'; font-size:12pt; font-weight:normal; color:#800000;                           }
</STYLE>
</HEAD>
<BODY>
	<H1>Test Report</H1>
	<BR/>
  	<xsl:apply-templates select="/TestRun/*"/>
</BODY>
</HTML>
</xsl:template>

<!-- ==================================================================== -->
<xsl:template match="FailedTests">
	<H2>FailedTests</H2>
	<xsl:choose>
	<xsl:when test="FailedTest">
		<TABLE>
			<TR>
				<TH width="100px">id</TH>
				<TH width="400px">Name</TH>
				<TH width="200px">FailureType</TH>
				<TH width="600px">Location</TH>
				<TH width="600px">Message</TH>
			</TR>
		  	<xsl:apply-templates select="FailedTest"/>
		</TABLE>
	</xsl:when>
	<xsl:otherwise>
	    <SPAN class="good">No failed test.</SPAN>
	</xsl:otherwise>
	</xsl:choose>
	<BR/>
</xsl:template>

<xsl:template match="FailedTest">
	<TR>
		<TD align="right"><xsl:value-of select="@id"/></TD>
		<TD><xsl:apply-templates select="Name"/></TD>
		<TD align="center"><xsl:apply-templates select="FailureType"/></TD>
		<TD><xsl:apply-templates select="Location"/></TD>
		<TD><xsl:apply-templates select="Message"/></TD>
	</TR>
</xsl:template>

<xsl:template match="Name|FailureType|Message"><xsl:value-of select="."/></xsl:template>

<xsl:template match="Location">
	<xsl:if test=".">
		line #<xsl:value-of select="Line"/> in <xsl:value-of select="File"/>
	</xsl:if>
</xsl:template>
  
<!-- ==================================================================== -->
<xsl:template match="SucessfulTests|SuccessfulTests">
	<H2>SuccessfulTests</H2>
	<xsl:choose>
	<xsl:when test="Test">
	<TABLE>
		<TR>
			<TH width="100px">id</TH>
			<TH width="400px">Name</TH>
		</TR>
	  	<xsl:apply-templates select="Test"/>
	</TABLE>
	</xsl:when>
	<xsl:otherwise>
	    <SPAN class="critical">No successful test.</SPAN>
	</xsl:otherwise>
	</xsl:choose>
	<BR/>
</xsl:template>

<xsl:template match="Test">
	<TR>
		<TD align="right"><xsl:value-of        select="@id"  /></TD>
		<TD              ><xsl:apply-templates select="Name" /></TD>
	</TR>
</xsl:template>

<!-- ==================================================================== -->
<xsl:template match="Statistics">
	<H2>Statistics</H2>
	<TABLE>
		<TR>
			<TH width="100px">Status</TH>
			<TH width="200px">Number</TH>
		</TR>

		<TR>
			<TD>Tests</TD>
			<TD align="right"><xsl:value-of select="Tests"/></TD>
		</TR>

		<TR>
			<TD>FailuresTotal</TD>
			<TD align="right"><xsl:value-of select="FailuresTotal"/></TD>
		</TR>

		<TR>
			<TD>Errors</TD>
			<TD align="right"><xsl:value-of select="Errors"/></TD>
		</TR>

		<TR>
			<TD>Failures</TD>
			<TD align="right"><xsl:value-of select="Failures"/></TD>
		</TR>
		
	</TABLE>
	<BR/>
</xsl:template>



</xsl:stylesheet>
