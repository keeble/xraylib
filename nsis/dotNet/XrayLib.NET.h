/*
	XrayLib.NET copyright (c) 2010-2011 Matthew Wormington. All rights reserved.
	
	File: XrfLibNET.h
	Author: Matthew Wormington
	Language: C++/CLI   
	Compiler: Microsoft Visual Studio 2010
	Created: September 4, 2010
	$Version:$
	$Revision:$
	$RevDate:$

	Description:
	Contains the definition of a managed wrapper class around the native 
	XrayLib API.

	"A library for X-ray�matter interaction cross sections for
	X-ray fluorescence applications".
	A. Brunetti, M. Sanchez del Rio, B. Golosio, A. Simionovici, A. Somogyi, 
	Spectrochimica Acta Part B 59 (2004) 1725�1731
	http://ftp.esrf.fr/pub/scisoft/xraylib/

	Notes:
	A singleton pattern has been used so that only one instance of the class is ever
	created. The Instance property provides a global point of access to the instance.
	The implementation is based on the Static Initialization example in the following
	Microsoft article: http://msdn.microsoft.com/en-us/library/ms998558.aspx


	XrayLib copyright (c) 2009, Bruno Golosio, Antonio Brunetti, Manuel Sanchez del 
	Rio, Tom Schoonjans and Teemu Ikonen. All rights reserved.

	Redistribution and use in source and binary forms, with or without
	modification, are permitted provided that the following conditions are met:
	* Redistributions of source code must retain the above copyright notice, this 
	  list of conditions and the following disclaimer.
	* Redistributions in binary form must reproduce the above copyright notice, this 
	  list of conditions and the following disclaimer 
	  in the documentation and/or other materials provided with the distribution.
	* The names of the contributors may not be used to endorse or promote products 
	  derived from this software without specific prior written permission.

	THIS SOFTWARE IS PROVIDED BY Bruno Golosio, Antonio Brunetti, Manuel Sanchez del Rio, 
	Tom Schoonjans, Teemu Ikonen and Matthew Wormington ''AS IS'' AND ANY EXPRESS OR IMPLIED 
	WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND 
	FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL Bruno Golosio, Antonio 
	Brunetti, Manuel Sanchez del Rio, Tom Schoonjans and Teemu Ikonen BE LIABLE FOR ANY 
	DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
	BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
	OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
	WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
	ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
	OF SUCH DAMAGE.
*/

#pragma once

using namespace System;

/// <summary>
/// A namespace that contains scientific classes.
/// </summary>
namespace Science {

	/// <summary>
	/// A custom exception that inherits from Exception and is thrown by the XrayLib class. 
	/// </summary>
	public ref class XrayLibException: Exception
	{
	public:
		// Overloading the constructor for passing the message associated with the exception
		XrayLibException(System::String ^message);
	};

	/// <summary>
	/// A managed wrapper around the XrayLib library for X-ray matter interaction cross sections 
	/// for X-ray fluorescence applications. 
	/// <para>The XrayLib is a library of X-ray matter interaction data for X-ray fluorescence,
	/// and other, applications. </para>
	/// <para>Reference:</para>
	/// <para>A. Brunetti, M. Sanchez del Rio, B. Golosio, A. Simionovici, A. Somogyi, 
	///	Spectrochimica Acta Part B 59 (2004) 1725�1731</para>
	/// <para>http://ftp.esrf.fr/pub/scisoft/xraylib/</para>
	/// </summary>
	public ref class XrayLib
	{
	private:
		static initonly XrayLib ^_instance = gcnew XrayLib();

		// Only the main lines are included in the following arrays
		static array<System::String^> ^IUPACLineNames = 
			{"KL3","KL2","KM3","KN2","KM2","L3M5","L3M4","L2M4","L3N5",
			"L1M3","L1M2","L3N1","L2N4","L1N2","L1N3","L2M1","L3M1"};

		// In the SiegbahnLineName array, the following notation is used:
		// a - alpha, b - beta, g - gamma, n - Nu, l - eta
		static array<System::String^> ^SiegbahnLineNames = 
			{"Ka1","Ka2","Kb1","Kb2","Kb3","La1","La2","Lb1","Lb2",
			"Lb3","Lb4","Lb6","Lg1","Lg2","Lg3","Ln","Ll"};
		static array<int> ^SiegbahnLines =
			{KA1_LINE,KA2_LINE,KB1_LINE,KB2_LINE,KB3_LINE,LA1_LINE,LA2_LINE,LB1_LINE,LB2_LINE,
			LB3_LINE,LB4_LINE,LB6_LINE,LG1_LINE,LG2_LINE,LG3_LINE,LN_LINE,LL_LINE};

		/// <summary>
		/// Constructor.
		/// </summary>
		XrayLib();

	public:
		#pragma region  Constants
		literal int VERSION_MAJOR = 2;
		literal int VERSION_MINOR = 15;
		literal double PI = 3.14159265359;

		// Values taken from physics.nist.gov
		literal double AVOGNUM = 0.602214179;    // Avogadro number (mol-1 * barn-1 * cm2) 
		literal double KEV2ANGST = 12.39841875;  // keV to Angstrom-1 conversion factor 
		literal double MEC2 = 510.998910;        // Electron rest mass (keV) 
		literal double RE2 = 0.079407877;        // Square of classical electron radius (barn)

		// IUPAC lines
		literal int KL1_LINE = -1;
		literal int KL2_LINE = -2;
		literal int KL3_LINE = -3;
		literal int KM1_LINE = -4;
		literal int KM2_LINE = -5;
		literal int KM3_LINE = -6;
		literal int KM4_LINE = -7;
		literal int KM5_LINE = -8;
		literal int KN1_LINE = -9;
		literal int KN2_LINE = -10;
		literal int KN3_LINE = -11;
		literal int KN4_LINE = -12;
		literal int KN5_LINE = -13;
		literal int KN6_LINE = -14;
		literal int KN7_LINE = -15;
		literal int KO_LINE = -16;
		literal int KO1_LINE = -17;
		literal int KO2_LINE = -18;
		literal int KO3_LINE = -19;
		literal int KO4_LINE = -20;
		literal int KO5_LINE = -21;
		literal int KO6_LINE = -22;
		literal int KO7_LINE = -23;
		literal int KP_LINE = -24;
		literal int KP1_LINE = -25;
		literal int KP2_LINE = -26;
		literal int KP3_LINE = -27;
		literal int KP4_LINE = -28;
		literal int KP5_LINE = -29;
		literal int L1L2_LINE = -30;
		literal int L1L3_LINE = -31;
		literal int L1M1_LINE = -32;
		literal int L1M2_LINE = -33;
		literal int L1M3_LINE = -34;
		literal int L1M4_LINE = -35;
		literal int L1M5_LINE = -36;
		literal int L1N1_LINE = -37;
		literal int L1N2_LINE = -38;
		literal int L1N3_LINE = -39;
		literal int L1N4_LINE = -40;
		literal int L1N5_LINE = -41;
		literal int L1N6_LINE = -42;
		literal int L1N67_LINE = -43;
		literal int L1N7_LINE = -44;
		literal int L1O1_LINE = -45;
		literal int L1O2_LINE = -46;
		literal int L1O3_LINE = -47;
		literal int L1O4_LINE = -48;
		literal int L1O45_LINE = -49;
		literal int L1O5_LINE = -50;
		literal int L1O6_LINE = -51;
		literal int L1O7_LINE = -52;
		literal int L1P1_LINE = -53;
		literal int L1P2_LINE = -54;
		literal int L1P23_LINE = -55;
		literal int L1P3_LINE = -56;
		literal int L1P4_LINE = -57;
		literal int L1P5_LINE = -58;
		literal int L2L3_LINE = -59;
		literal int L2M1_LINE = -60;
		literal int L2M2_LINE = -61;
		literal int L2M3_LINE = -62;
		literal int L2M4_LINE = -63;
		literal int L2M5_LINE = -64;
		literal int L2N1_LINE = -65;
		literal int L2N2_LINE = -66;
		literal int L2N3_LINE = -67;
		literal int L2N4_LINE = -68;
		literal int L2N5_LINE = -69;
		literal int L2N6_LINE = -70;
		literal int L2N7_LINE = -71;
		literal int L2O1_LINE = -72;
		literal int L2O2_LINE = -73;
		literal int L2O3_LINE = -74;
		literal int L2O4_LINE = -75;
		literal int L2O5_LINE = -76;
		literal int L2O6_LINE = -77;
		literal int L2O7_LINE = -78;
		literal int L2P1_LINE = -79;
		literal int L2P2_LINE = -80;
		literal int L2P23_LINE = -81;
		literal int L2P3_LINE = -82;
		literal int L2P4_LINE = -83;
		literal int L2P5_LINE = -84;
		literal int L2Q1_LINE = -85;
		literal int L3M1_LINE = -86;
		literal int L3M2_LINE = -87;
		literal int L3M3_LINE = -88;
		literal int L3M4_LINE = -89;
		literal int L3M5_LINE = -90;
		literal int L3N1_LINE = -91;
		literal int L3N2_LINE = -92;
		literal int L3N3_LINE = -93;
		literal int L3N4_LINE = -94;
		literal int L3N5_LINE = -95;
		literal int L3N6_LINE = -96;
		literal int L3N7_LINE = -97;
		literal int L3O1_LINE = -98;
		literal int L3O2_LINE = -99;
		literal int L3O3_LINE = -100;
		literal int L3O4_LINE = -101;
		literal int L3O45_LINE = -102;
		literal int L3O5_LINE = -103;
		literal int L3O6_LINE = -104;
		literal int L3O7_LINE = -105;
		literal int L3P1_LINE = -106;
		literal int L3P2_LINE = -107;
		literal int L3P23_LINE = -108;
		literal int L3P3_LINE = -109;
		literal int L3P4_LINE = -110;
		literal int L3P45_LINE = -111;
		literal int L3P5_LINE = -112;
		literal int L3Q1_LINE = -113;
		literal int M1M2_LINE = -114;
		literal int M1M3_LINE = -115;
		literal int M1M4_LINE = -116;
		literal int M1M5_LINE = -117;
		literal int M1N1_LINE = -118;
		literal int M1N2_LINE = -119;
		literal int M1N3_LINE = -120;
		literal int M1N4_LINE = -121;
		literal int M1N5_LINE = -122;
		literal int M1N6_LINE = -123;
		literal int M1N7_LINE = -124;
		literal int M1O1_LINE = -125;
		literal int M1O2_LINE = -126;
		literal int M1O3_LINE = -127;
		literal int M1O4_LINE = -128;
		literal int M1O5_LINE = -129;
		literal int M1O6_LINE = -130;
		literal int M1O7_LINE = -131;
		literal int M1P1_LINE = -132;
		literal int M1P2_LINE = -133;
		literal int M1P3_LINE = -134;
		literal int M1P4_LINE = -135;
		literal int M1P5_LINE = -136;
		literal int M2M3_LINE = -137;
		literal int M2M4_LINE = -138;
		literal int M2M5_LINE = -139;
		literal int M2N1_LINE = -140;
		literal int M2N2_LINE = -141;
		literal int M2N3_LINE = -142;
		literal int M2N4_LINE = -143;
		literal int M2N5_LINE = -144;
		literal int M2N6_LINE = -145;
		literal int M2N7_LINE = -146;
		literal int M2O1_LINE = -147;
		literal int M2O2_LINE = -148;
		literal int M2O3_LINE = -149;
		literal int M2O4_LINE = -150;
		literal int M2O5_LINE = -151;
		literal int M2O6_LINE = -152;
		literal int M2O7_LINE = -153;
		literal int M2P1_LINE = -154;
		literal int M2P2_LINE = -155;
		literal int M2P3_LINE = -156;
		literal int M2P4_LINE = -157;
		literal int M2P5_LINE = -158;
		literal int M3M4_LINE = -159;
		literal int M3M5_LINE = -160;
		literal int M3N1_LINE = -161;
		literal int M3N2_LINE = -162;
		literal int M3N3_LINE = -163;
		literal int M3N4_LINE = -164;
		literal int M3N5_LINE = -165;
		literal int M3N6_LINE = -166;
		literal int M3N7_LINE = -167;
		literal int M3O1_LINE = -168;
		literal int M3O2_LINE = -169;
		literal int M3O3_LINE = -170;
		literal int M3O4_LINE = -171;
		literal int M3O5_LINE = -172;
		literal int M3O6_LINE = -173;
		literal int M3O7_LINE = -174;
		literal int M3P1_LINE = -175;
		literal int M3P2_LINE = -176;
		literal int M3P3_LINE = -177;
		literal int M3P4_LINE = -178;
		literal int M3P5_LINE = -179;
		literal int M3Q1_LINE = -180;
		literal int M4M5_LINE = -181;
		literal int M4N1_LINE = -182;
		literal int M4N2_LINE = -183;
		literal int M4N3_LINE = -184;
		literal int M4N4_LINE = -185;
		literal int M4N5_LINE = -186;
		literal int M4N6_LINE = -187;
		literal int M4N7_LINE = -188;
		literal int M4O1_LINE = -189;
		literal int M4O2_LINE = -190;
		literal int M4O3_LINE = -191;
		literal int M4O4_LINE = -192;
		literal int M4O5_LINE = -193;
		literal int M4O6_LINE = -194;
		literal int M4O7_LINE = -195;
		literal int M4P1_LINE = -196;
		literal int M4P2_LINE = -197;
		literal int M4P3_LINE = -198;
		literal int M4P4_LINE = -199;
		literal int M4P5_LINE = -200;
		literal int M5N1_LINE = -201;
		literal int M5N2_LINE = -202;
		literal int M5N3_LINE = -203;
		literal int M5N4_LINE = -204;
		literal int M5N5_LINE = -205;
		literal int M5N6_LINE = -206;
		literal int M5N7_LINE = -207;
		literal int M5O1_LINE = -208;
		literal int M5O2_LINE = -209;
		literal int M5O3_LINE = -210;
		literal int M5O4_LINE = -211;
		literal int M5O5_LINE = -212;
		literal int M5O6_LINE = -213;
		literal int M5O7_LINE = -214;
		literal int M5P1_LINE = -215;
		literal int M5P2_LINE = -216;
		literal int M5P3_LINE = -217;
		literal int M5P4_LINE = -218;
		literal int M5P5_LINE = -219;
		literal int N1N2_LINE = -220;
		literal int N1N3_LINE = -221;
		literal int N1N4_LINE = -222;
		literal int N1N5_LINE = -223;
		literal int N1N6_LINE = -224;
		literal int N1N7_LINE = -225;
		literal int N1O1_LINE = -226;
		literal int N1O2_LINE = -227;
		literal int N1O3_LINE = -228;
		literal int N1O4_LINE = -229;
		literal int N1O5_LINE = -230;
		literal int N1O6_LINE = -231;
		literal int N1O7_LINE = -232;
		literal int N1P1_LINE = -233;
		literal int N1P2_LINE = -234;
		literal int N1P3_LINE = -235;
		literal int N1P4_LINE = -236;
		literal int N1P5_LINE = -237;
		literal int N2N3_LINE = -238;
		literal int N2N4_LINE = -239;
		literal int N2N5_LINE = -240;
		literal int N2N6_LINE = -241;
		literal int N2N7_LINE = -242;
		literal int N2O1_LINE = -243;
		literal int N2O2_LINE = -244;
		literal int N2O3_LINE = -245;
		literal int N2O4_LINE = -246;
		literal int N2O5_LINE = -247;
		literal int N2O6_LINE = -248;
		literal int N2O7_LINE = -249;
		literal int N2P1_LINE = -250;
		literal int N2P2_LINE = -251;
		literal int N2P3_LINE = -252;
		literal int N2P4_LINE = -253;
		literal int N2P5_LINE = -254;
		literal int N3N4_LINE = -255;
		literal int N3N5_LINE = -256;
		literal int N3N6_LINE = -257;
		literal int N3N7_LINE = -258;
		literal int N3O1_LINE = -259;
		literal int N3O2_LINE = -260;
		literal int N3O3_LINE = -261;
		literal int N3O4_LINE = -262;
		literal int N3O5_LINE = -263;
		literal int N3O6_LINE = -264;
		literal int N3O7_LINE = -265;
		literal int N3P1_LINE = -266;
		literal int N3P2_LINE = -267;
		literal int N3P3_LINE = -268;
		literal int N3P4_LINE = -269;
		literal int N3P5_LINE = -270;
		literal int N4N5_LINE = -271;
		literal int N4N6_LINE = -272;
		literal int N4N7_LINE = -273;
		literal int N4O1_LINE = -274;
		literal int N4O2_LINE = -275;
		literal int N4O3_LINE = -276;
		literal int N4O4_LINE = -277;
		literal int N4O5_LINE = -278;
		literal int N4O6_LINE = -279;
		literal int N4O7_LINE = -280;
		literal int N4P1_LINE = -281;
		literal int N4P2_LINE = -282;
		literal int N4P3_LINE = -283;
		literal int N4P4_LINE = -284;
		literal int N4P5_LINE = -285;
		literal int N5N6_LINE = -286;
		literal int N5N7_LINE = -287;
		literal int N5O1_LINE = -288;
		literal int N5O2_LINE = -289;
		literal int N5O3_LINE = -290;
		literal int N5O4_LINE = -291;
		literal int N5O5_LINE = -292;
		literal int N5O6_LINE = -293;
		literal int N5O7_LINE = -294;
		literal int N5P1_LINE = -295;
		literal int N5P2_LINE = -296;
		literal int N5P3_LINE = -297;
		literal int N5P4_LINE = -298;
		literal int N5P5_LINE = -299;
		literal int N6N7_LINE = -300;
		literal int N6O1_LINE = -301;
		literal int N6O2_LINE = -302;
		literal int N6O3_LINE = -303;
		literal int N6O4_LINE = -304;
		literal int N6O5_LINE = -305;
		literal int N6O6_LINE = -306;
		literal int N6O7_LINE = -307;
		literal int N6P1_LINE = -308;
		literal int N6P2_LINE = -309;
		literal int N6P3_LINE = -310;
		literal int N6P4_LINE = -311;
		literal int N6P5_LINE = -312;
		literal int N7O1_LINE = -313;
		literal int N7O2_LINE = -314;
		literal int N7O3_LINE = -315;
		literal int N7O4_LINE = -316;
		literal int N7O5_LINE = -317;
		literal int N7O6_LINE = -318;
		literal int N7O7_LINE = -319;
		literal int N7P1_LINE = -320;
		literal int N7P2_LINE = -321;
		literal int N7P3_LINE = -322;
		literal int N7P4_LINE = -323;
		literal int N7P5_LINE = -324;
		literal int O1O2_LINE = -325;
		literal int O1O3_LINE = -326;
		literal int O1O4_LINE = -327;
		literal int O1O5_LINE = -328;
		literal int O1O6_LINE = -329;
		literal int O1O7_LINE = -330;
		literal int O1P1_LINE = -331;
		literal int O1P2_LINE = -332;
		literal int O1P3_LINE = -333;
		literal int O1P4_LINE = -334;
		literal int O1P5_LINE = -335;
		literal int O2O3_LINE = -336;
		literal int O2O4_LINE = -337;
		literal int O2O5_LINE = -338;
		literal int O2O6_LINE = -339;
		literal int O2O7_LINE = -340;
		literal int O2P1_LINE = -341;
		literal int O2P2_LINE = -342;
		literal int O2P3_LINE = -343;
		literal int O2P4_LINE = -344;
		literal int O2P5_LINE = -345;
		literal int O3O4_LINE = -346;
		literal int O3O5_LINE = -347;
		literal int O3O6_LINE = -348;
		literal int O3O7_LINE = -349;
		literal int O3P1_LINE = -350;
		literal int O3P2_LINE = -351;
		literal int O3P3_LINE = -352;
		literal int O3P4_LINE = -353;
		literal int O3P5_LINE = -354;
		literal int O4O5_LINE = -355;
		literal int O4O6_LINE = -356;
		literal int O4O7_LINE = -357;
		literal int O4P1_LINE = -358;
		literal int O4P2_LINE = -359;
		literal int O4P3_LINE = -360;
		literal int O4P4_LINE = -361;
		literal int O4P5_LINE = -362;
		literal int O5O6_LINE = -363;
		literal int O5O7_LINE = -364;
		literal int O5P1_LINE = -365;
		literal int O5P2_LINE = -366;
		literal int O5P3_LINE = -367;
		literal int O5P4_LINE = -368;
		literal int O5P5_LINE = -369;
		literal int O6O7_LINE = -370;
		literal int O6P4_LINE = -371;
		literal int O6P5_LINE = -372;
		literal int O7P4_LINE = -373;
		literal int O7P5_LINE = -374;
		literal int P1P2_LINE = -375;
		literal int P1P3_LINE = -376;
		literal int P1P4_LINE = -377;
		literal int P1P5_LINE = -378;
		literal int P2P3_LINE = -379;
		literal int P2P4_LINE = -380;
		literal int P2P5_LINE = -381;
		literal int P3P4_LINE = -382;
		literal int P3P5_LINE = -383;

		// Siegbahn notation
		// according to Table VIII.2 from Nomenclature system for X-ray spectroscopy
		// Linegroups -> usage is discouraged
		literal int KA_LINE = 0;            // Weighted average of KA1 & KA2
		literal int KB_LINE = 1;            // Weighted average of KB1 & KB3
		literal int LA_LINE = 2;            // LA1
		literal int LB_LINE = 3;            // LB1

  		// Single lines
		literal int KA1_LINE = KL3_LINE;
		literal int KA2_LINE = KL2_LINE;
		literal int KB1_LINE = KM3_LINE;
		literal int KB2_LINE = KN3_LINE;
		literal int KB3_LINE = KM2_LINE;
		literal int KB4_LINE = KN5_LINE;
		literal int KB5_LINE = KM5_LINE;

		literal int LA1_LINE = L3M5_LINE;
		literal int LA2_LINE = L3M4_LINE;
		literal int LB1_LINE = L2M4_LINE;
		literal int LB2_LINE = L3N5_LINE;
		literal int LB3_LINE = L1M3_LINE;
		literal int LB4_LINE = L1M2_LINE;
		literal int LB5_LINE = L3O45_LINE;
		literal int LB6_LINE = L3N1_LINE;
		literal int LB7_LINE = L3O1_LINE;
		literal int LB9_LINE = L1M5_LINE;
		literal int LB10_LINE = L1M4_LINE;
		literal int LB15_LINE = L3N4_LINE;
		literal int LB17_LINE = L2M3_LINE;
		literal int LG1_LINE = L2N4_LINE;
		literal int LG2_LINE = L1N2_LINE;
		literal int LG3_LINE = L1N3_LINE;
		literal int LG4_LINE = L1O3_LINE;
		literal int LG5_LINE = L2N1_LINE;
		literal int LG6_LINE = L2O4_LINE;
		literal int LG8_LINE = L2O1_LINE;
		literal int LE_LINE = L2M1_LINE;
		literal int LN_LINE = L2M1_LINE;
		literal int LL_LINE = L3M1_LINE;
		literal int LS_LINE = L3M3_LINE;
		literal int LT_LINE = L3M2_LINE;
		literal int LU_LINE = L3N6_LINE;
		literal int LV_LINE = L2N6_LINE;

		literal int MA1_LINE = M5N7_LINE;
		literal int MA2_LINE = M5N6_LINE;
		literal int MB_LINE = M4N6_LINE;
		literal int MG_LINE = M3N5_LINE;

		// Shells
		literal int K_SHELL = 0;
		literal int L1_SHELL = 1;
		literal int L2_SHELL = 2;
		literal int L3_SHELL = 3;
		literal int M1_SHELL = 4;
		literal int M2_SHELL = 5;
		literal int M3_SHELL = 6;
		literal int M4_SHELL = 7;
		literal int M5_SHELL = 8;
		literal int N1_SHELL = 9;
		literal int N2_SHELL = 10;
		literal int N3_SHELL = 11;
		literal int N4_SHELL = 12;
		literal int N5_SHELL = 13;
		literal int N6_SHELL = 14;
		literal int N7_SHELL = 15;
		literal int O1_SHELL = 16;
		literal int O2_SHELL = 17;
		literal int O3_SHELL = 18;
		literal int O4_SHELL = 19;
		literal int O5_SHELL = 20;
		literal int O6_SHELL = 21;
		literal int O7_SHELL = 22;
		literal int P1_SHELL = 23;
		literal int P2_SHELL = 24;
		literal int P3_SHELL = 25;
		literal int P4_SHELL = 26;
		literal int P5_SHELL = 27;
		literal int Q1_SHELL = 28;
		literal int Q2_SHELL = 29;
		literal int Q3_SHELL = 30;

		// Transitions
		literal int F1_TRANS = 0;
		literal int F12_TRANS = 1;
		literal int F13_TRANS = 2;
		literal int FP13_TRANS = 3;
		literal int F23_TRANS = 4;

		literal int FL12_TRANS = 1;
		literal int FL13_TRANS = 2;
		literal int FLP13_TRANS = 3;
		literal int FL23_TRANS = 4;
		literal int FM12_TRANS = 5;
		literal int FM13_TRANS = 6;
		literal int FM14_TRANS = 7;
		literal int FM15_TRANS = 8;
		literal int FM23_TRANS = 9;
		literal int FM24_TRANS = 10;
		literal int FM25_TRANS = 11;
		literal int FM34_TRANS = 12;
		literal int FM35_TRANS = 13;
		literal int FM45_TRANS = 14;

		// Auger transitions
		literal int K_L1L1_AUGER = 0;
		literal int K_L1L2_AUGER = 1;
		literal int K_L1L3_AUGER = 2;
		literal int K_L1M1_AUGER = 3;
		literal int K_L1M2_AUGER = 4;
		literal int K_L1M3_AUGER = 5;
		literal int K_L1M4_AUGER = 6;
		literal int K_L1M5_AUGER = 7;
		literal int K_L2L1_AUGER = 8;
		literal int K_L2L2_AUGER = 9;
		literal int K_L2L3_AUGER = 10;
		literal int K_L2M1_AUGER = 11;
		literal int K_L2M2_AUGER = 12;
		literal int K_L2M3_AUGER = 13;
		literal int K_L2M4_AUGER = 14;
		literal int K_L2M5_AUGER = 15;
		literal int K_L3L1_AUGER = 16;
		literal int K_L3L2_AUGER = 17;
		literal int K_L3L3_AUGER = 18;
		literal int K_L3M1_AUGER = 19;
		literal int K_L3M2_AUGER = 20;
		literal int K_L3M3_AUGER = 21;
		literal int K_L3M4_AUGER = 22;
		literal int K_L3M5_AUGER = 23;
		literal int K_M1L1_AUGER = 24;
		literal int K_M1L2_AUGER = 25;
		literal int K_M1L3_AUGER = 26;
		literal int K_M1M1_AUGER = 27;
		literal int K_M1M2_AUGER = 28;
		literal int K_M1M3_AUGER = 29;
		literal int K_M1M4_AUGER = 30;
		literal int K_M1M5_AUGER = 31;
		literal int K_M2L1_AUGER = 32;
		literal int K_M2L2_AUGER = 33;
		literal int K_M2L3_AUGER = 34;
		literal int K_M2M1_AUGER = 35;
		literal int K_M2M2_AUGER = 36;
		literal int K_M2M3_AUGER = 37;
		literal int K_M2M4_AUGER = 38;
		literal int K_M2M5_AUGER = 39;
		literal int K_M3L1_AUGER = 40;
		literal int K_M3L2_AUGER = 41;
		literal int K_M3L3_AUGER = 42;
		literal int K_M3M1_AUGER = 43;
		literal int K_M3M2_AUGER = 44;
		literal int K_M3M3_AUGER = 45;
		literal int K_M3M4_AUGER = 46;
		literal int K_M3M5_AUGER = 47;
		literal int K_M4L1_AUGER = 48;
		literal int K_M4L2_AUGER = 49;
		literal int K_M4L3_AUGER = 50;
		literal int K_M4M1_AUGER = 51;
		literal int K_M4M2_AUGER = 52;
		literal int K_M4M3_AUGER = 53;
		literal int K_M4M4_AUGER = 54;
		literal int K_M4M5_AUGER = 55;
		literal int K_M5L1_AUGER = 56;
		literal int K_M5L2_AUGER = 57;
		literal int K_M5L3_AUGER = 58;
		literal int K_M5M1_AUGER = 59;
		literal int K_M5M2_AUGER = 60;
		literal int K_M5M3_AUGER = 61;
		literal int K_M5M4_AUGER = 62;
		literal int K_M5M5_AUGER = 63;
		literal int L1_L2L2_AUGER = 64;
		literal int L1_L2L3_AUGER = 65;
		literal int L1_L2M1_AUGER = 66;
		literal int L1_L2M2_AUGER = 67;
		literal int L1_L2M3_AUGER = 68;
		literal int L1_L2M4_AUGER = 69;
		literal int L1_L2M5_AUGER = 70;
		literal int L1_L3L2_AUGER = 71;
		literal int L1_L3L3_AUGER = 72;
		literal int L1_L3M1_AUGER = 73;
		literal int L1_L3M2_AUGER = 74;
		literal int L1_L3M3_AUGER = 75;
		literal int L1_L3M4_AUGER = 76;
		literal int L1_L3M5_AUGER = 77;
		literal int L1_M1L2_AUGER = 78;
		literal int L1_M1L3_AUGER = 79;
		literal int L1_M1M1_AUGER = 80;
		literal int L1_M1M2_AUGER = 81;
		literal int L1_M1M3_AUGER = 82;
		literal int L1_M1M4_AUGER = 83;
		literal int L1_M1M5_AUGER = 84;
		literal int L1_M2L2_AUGER = 85;
		literal int L1_M2L3_AUGER = 86;
		literal int L1_M2M1_AUGER = 87;
		literal int L1_M2M2_AUGER = 88;
		literal int L1_M2M3_AUGER = 89;
		literal int L1_M2M4_AUGER = 90;
		literal int L1_M2M5_AUGER = 91;
		literal int L1_M3L2_AUGER = 92;
		literal int L1_M3L3_AUGER = 93;
		literal int L1_M3M1_AUGER = 94;
		literal int L1_M3M2_AUGER = 95;
		literal int L1_M3M3_AUGER = 96;
		literal int L1_M3M4_AUGER = 97;
		literal int L1_M3M5_AUGER = 98;
		literal int L1_M4L2_AUGER = 99;
		literal int L1_M4L3_AUGER = 100;
		literal int L1_M4M1_AUGER = 101;
		literal int L1_M4M2_AUGER = 102;
		literal int L1_M4M3_AUGER = 103;
		literal int L1_M4M4_AUGER = 104;
		literal int L1_M4M5_AUGER = 105;
		literal int L1_M5L2_AUGER = 106;
		literal int L1_M5L3_AUGER = 107;
		literal int L1_M5M1_AUGER = 108;
		literal int L1_M5M2_AUGER = 109;
		literal int L1_M5M3_AUGER = 110;
		literal int L1_M5M4_AUGER = 111;
		literal int L1_M5M5_AUGER = 112;
		literal int L2_L3L3_AUGER = 113;
		literal int L2_L3M1_AUGER = 114;
		literal int L2_L3M2_AUGER = 115;
		literal int L2_L3M3_AUGER = 116;
		literal int L2_L3M4_AUGER = 117;
		literal int L2_L3M5_AUGER = 118;
		literal int L2_M1L3_AUGER = 119;
		literal int L2_M1M1_AUGER = 120;
		literal int L2_M1M2_AUGER = 121;
		literal int L2_M1M3_AUGER = 122;
		literal int L2_M1M4_AUGER = 123;
		literal int L2_M1M5_AUGER = 124;
		literal int L2_M2L3_AUGER = 125;
		literal int L2_M2M1_AUGER = 126;
		literal int L2_M2M2_AUGER = 127;
		literal int L2_M2M3_AUGER = 128;
		literal int L2_M2M4_AUGER = 129;
		literal int L2_M2M5_AUGER = 130;
		literal int L2_M3L3_AUGER = 131;
		literal int L2_M3M1_AUGER = 132;
		literal int L2_M3M2_AUGER = 133;
		literal int L2_M3M3_AUGER = 134;
		literal int L2_M3M4_AUGER = 135;
		literal int L2_M3M5_AUGER = 136;
		literal int L2_M4L3_AUGER = 137;
		literal int L2_M4M1_AUGER = 138;
		literal int L2_M4M2_AUGER = 139;
		literal int L2_M4M3_AUGER = 140;
		literal int L2_M4M4_AUGER = 141;
		literal int L2_M4M5_AUGER = 142;
		literal int L2_M5L3_AUGER = 143;
		literal int L2_M5M1_AUGER = 144;
		literal int L2_M5M2_AUGER = 145;
		literal int L2_M5M3_AUGER = 146;
		literal int L2_M5M4_AUGER = 147;
		literal int L2_M5M5_AUGER = 148;
		literal int L3_M1M1_AUGER = 149;
		literal int L3_M1M2_AUGER = 150;
		literal int L3_M1M3_AUGER = 151;
		literal int L3_M1M4_AUGER = 152;
		literal int L3_M1M5_AUGER = 153;
		literal int L3_M2M1_AUGER = 154;
		literal int L3_M2M2_AUGER = 155;
		literal int L3_M2M3_AUGER = 156;
		literal int L3_M2M4_AUGER = 157;
		literal int L3_M2M5_AUGER = 158;
		literal int L3_M3M1_AUGER = 159;
		literal int L3_M3M2_AUGER = 160;
		literal int L3_M3M3_AUGER = 161;
		literal int L3_M3M4_AUGER = 162;
		literal int L3_M3M5_AUGER = 163;
		literal int L3_M4M1_AUGER = 164;
		literal int L3_M4M2_AUGER = 165;
		literal int L3_M4M3_AUGER = 166;
		literal int L3_M4M4_AUGER = 167;
		literal int L3_M4M5_AUGER = 168;
		literal int L3_M5M1_AUGER = 169;
		literal int L3_M5M2_AUGER = 170;
		literal int L3_M5M3_AUGER = 171;
		literal int L3_M5M4_AUGER = 172;
		literal int L3_M5M5_AUGER = 173;
		literal int M1_M2M2_AUGER = 174;
		literal int M1_M2M3_AUGER = 175;
		literal int M1_M2M4_AUGER = 176;
		literal int M1_M2M5_AUGER = 177;
		literal int M1_M3M2_AUGER = 178;
		literal int M1_M3M3_AUGER = 179;
		literal int M1_M3M4_AUGER = 180;
		literal int M1_M3M5_AUGER = 181;
		literal int M1_M4M2_AUGER = 182;
		literal int M1_M4M3_AUGER = 183;
		literal int M1_M4M4_AUGER = 184;
		literal int M1_M4M5_AUGER = 185;
		literal int M1_M5M2_AUGER = 186;
		literal int M1_M5M3_AUGER = 187;
		literal int M1_M5M4_AUGER = 188;
		literal int M1_M5M5_AUGER = 189;
		literal int M2_M3M3_AUGER = 190;
		literal int M2_M3M4_AUGER = 191;
		literal int M2_M3M5_AUGER = 192;
		literal int M2_M4M3_AUGER = 193;
		literal int M2_M4M4_AUGER = 194;
		literal int M2_M4M5_AUGER = 195;
		literal int M2_M5M3_AUGER = 196;
		literal int M2_M5M4_AUGER = 197;
		literal int M2_M5M5_AUGER = 198;
		literal int M3_M4M4_AUGER = 199;
		literal int M3_M4M5_AUGER = 200;
		literal int M3_M5M4_AUGER = 201;
		literal int M3_M5M5_AUGER = 202;
		literal int M4_M5M5_AUGER = 203;
		#pragma endregion

		/// <summary>
		/// Gets the single instance of the class.
		/// </summary>
		static property XrayLib ^Instance
		{
			XrayLib ^get()
			{
				return _instance;
			}
		}

		// Error Handling
		/// <summary>
		/// Sets the hard error exit code.
		/// </summary>
		/// <param name="hard_exit">Hard exit code</param>
		void SetHardExit(int hard_exit);

		/// <summary>
		/// Sets the exit status code.
		/// </summary>
		/// <param name="exit_status">Exit status code</param>
		void SetExitStatus(int exit_status);

		/// <summary>
		/// Gets the exit status code.
		/// </summary>
		/// <returns>Exit status code</returns>
		int GetExitStatus();

		/// <summary>	
		/// Sets whether, or not, error messages are displayed. 
		/// </summary>
		/// <param name="status">status is non-zero to display messages</param>
		void SetErrorMessages(int status);

		/// <summary>Gets whether, or now, error messages are displayed. </summary>
		/// <returns>Returns a non-zero if messages are displayed</returns>
		int GetErrorMessages(void);

		/// <summary>
		/// Gets the atomic weight of the element with the specified atomic number.
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <returns>Atomic weight</returns>
		double AtomicWeight(int Z);

		/// <summary>
		/// Gets element information for the specified atomic number.
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <returns>Element information</returns>
		Science::ElementData GetElementData(int Z);

		// Cross sections 
		/// <summary>
		/// Calculates the total cross section.
		/// </summary>
		/// <param name="Z">Atomic number of the element</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (cm2/g)</returns>
		double CS_Total(int Z, double E);

		/// <summary>
		/// Calculates the photoelectric absorption cross section.
		/// </summary>
		/// <param name="Z">Atomic number of the element</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (cm2/g)</returns>
		double CS_Photo(int Z, double E);

		/// <summary>
		/// Calculates the Rayleigh scattering cross section.
		/// </summary>
		/// <param name="Z">Atomic number of the element</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (cm2/g)</returns>
		double CS_Rayl(int Z, double E);

		/// <summary>
		/// Calculates the Compton scattering cross section.
		/// </summary>
		/// <param name="Z">Atomic number of the element</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (cm2/g)</returns>
		double CS_Compt(int Z, double E);

		/// <summary>
		/// Calculates the total cross section.
		/// </summary>
		/// <param name="Z">Atomic number of the element</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns>
		double CSb_Total(int Z, double E);

		/// <summary>
		/// Calculates the photoelectric absorption cross section.
		/// </summary>
		/// <param name="Z">Atomic number of the element</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns>
		double CSb_Photo(int Z, double E);

		/// <summary>
		/// Calculates the Rayleigh scattering cross section.
		/// </summary>
		/// <param name="Z">Atomic number of the element</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns>
		double CSb_Rayl(int Z, double E);

		/// <summary>
		/// Calculates the Compton scattering cross section.
		/// </summary>
		/// <param name="Z">Atomic number of the element</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns>
		double CSb_Compt(int Z, double E);

		/// <summary>
		/// Calculates the total Klein-Nishina cross section.
		/// </summary>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns>
		double CS_KN(double E);

		// Unpolarized differential scattering cross sections
		/// <summary>
		/// Calculates the Thomson differential scattering cross section.
		/// </summary>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <returns>Cross section (barn)</returns>
		double DCS_Thoms(double theta);

		/// <summary>
		/// Calculates the Klein-Nishina differential scattering cross section.
		/// </summary>
		/// <param name="E">Energy (keV)</param>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <returns>Cross section (barn)</returns>
		double DCS_KN(double E, double theta);

		/// <summary>
		/// Calculates the Rayleigh differential scattering cross section.
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="E">Energy (keV)</param>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <returns>Cross section (cm2/g/sterad)</returns>
		double DCS_Rayl(int Z, double E, double theta);

		/// <summary>
		/// Calculates the Compton differential scattering cross section.
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="E">Energy (keV)</param>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <returns>Cross section (cm2/g/sterad)</returns>
		double DCS_Compt(int Z, double E, double theta);

		/// <summary>
		/// Calculates the Rayleigh differential scattering cross section.
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="E">Energy (keV)</param>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <returns>Cross section (barn)</returns>
		double DCSb_Rayl(int Z, double E, double theta);

		/// <summary>
		/// Calculates the Compton differential scattering cross section.
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="E">Energy (keV)</param>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <returns>Cross section (barn)</returns>
		double DCSb_Compt(int Z, double E, double theta);

		// Polarized differential scattering cross sections
		/// <summary>
		/// Calculates the Thomson differential scattering cross section for polarized beam.
		/// </summary>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <param name="phi">Scattering azimuthal angle (rad)</param>
		/// <returns>Cross section (barn)</returns>
		double DCSP_Thoms(double theta, double phi);

		// Polarized differential scattering cross sections
		/// <summary>
		/// Calculates the Klein-Nishina differential scattering cross section for polarized beam.
		/// </summary>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <param name="phi">Scattering azimuthal angle (rad)</param>
		/// <returns>Cross section (barn)</returns>
		double DCSP_KN(double E, double theta, double phi);

		/// <summary>
		/// Calculates the Rayleigh differential scattering cross section for polarized beam.
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="E">Energy (keV)</param>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <param name="phi">Scattering azimuthal angle (rad)</param>
		/// <returns>Cross section (cm2/g/sterad)</returns>
		double DCSP_Rayl(int Z, double E, double theta, double phi);

		/// <summary>
		/// Calculates the Compton differential scattering cross section for polarized beam.
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="E">Energy (keV)</param>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <param name="phi">Scattering azimuthal angle (rad)</param>
		/// <returns>Cross section (cm2/g/sterad)</returns>
		double DCSP_Compt(int Z, double E, double theta, double phi);

		/// <summary>
		/// Calculates the Rayleigh differential scattering cross section for polarized beam.
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="E">Energy (keV)</param>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <param name="phi">Scattering azimuthal angle (rad)</param>
		/// <returns>Cross section (barn)</returns>
		double DCSPb_Rayl(int Z, double E, double theta, double phi);

		/// <summary>
		/// Calculates the Compton differential scattering cross section for polarized beam.
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="E">Energy (keV)</param>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <param name="phi">Scattering azimuthal angle (rad)</param>
		/// <returns>Cross section (barn)</returns>
		double DCSPb_Compt(int Z, double E, double theta, double phi);

		// Scattering factors
		/// <summary>
		/// Calculates the Atomic form factor for Rayleigh scattering.
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="q">Momentum transfer</param>
		/// <returns>Form factor</returns> 
		double FF_Rayl(int Z, double q);

		/// <summary>
		/// Calculates the Incoherent scattering function for Compton scattering.
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="q">Momentum transfer</param>
		/// <returns>Form factor</returns> 
		double  SF_Compt(int Z, double q);

		/// <summary>
		/// Calculates the Momentum transfer for X-ray photon scattering.
		/// </summary>
		/// <param name="E">Energy (keV)</param>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <returns>Momentum transfer (1/A)</returns> 
		double  MomentTransf(double E, double theta);

		/// <summary>
		/// Gets X-ray fluorescent line energy.
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="line">Emission line ID</param>
		/// <returns>X-ray fluorescent line energy (keV)</returns> 
		double LineEnergy(int Z, int line);

		/// <summary>
		/// Gets the fluorescence yield 
		/// </summary>
		/// <param name="Z">Atomic number of the element</param>
		/// <param name="shell">Atomic shell ID</param>
		/// <returns>Fluorescence yield</returns> 
		double FluorYield(int Z, int shell);

		/// <summary>
		/// Gets the Coster-Kronig transition probability
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="trans">Atomic transition ID</param>
		/// <returns>Transition probability</returns> 
		double CosKronTransProb(int Z, int trans);

		/// <summary>
		/// Gets the absorption-edge energy     
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="shell">Atomic shell ID</param>
		/// <returns>Edge energy (keV)</returns> 
		double EdgeEnergy(int Z, int shell);

		/// <summary>
		/// Gets the jump ratio     
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="shell">Atomic shell ID</param>
		/// <returns>Jump ratio</returns> 
		double JumpFactor(int Z, int shell);

		/// <summary>
		/// Calculates the fluorescent line cross section    
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="line">Atomic line ID</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (cm2/g)</returns> 
		double CS_FluorLine(int Z, int line, double E);

		/// <summary>
		/// Calculates the fluorescent line cross section    
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="line">Atomic line ID</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns> 
		double CSb_FluorLine(int Z, int line, double E);

		/// <summary>
		/// Gets the fractional radiative rate    
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="line">Atomic line ID</param>
		/// <returns>Fractional radiative rate</returns> 
		double RadRate(int Z, int line);

		/// <summary>
		/// Calculates the photon energy after Compton scattering   
		/// </summary>
		/// <param name="E0">Photon energy before scattering (keV)</param>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <returns>Energy after scattering (keV)</returns> 
		double ComptonEnergy(double E0, double theta);

		// Anomalous scattering factors
		/// <summary>
		/// Calculates the real-part of the anomalous scattering factor 
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Real-part of anomalous scattering factor</returns> 
		double Fi(int Z, double E);
		
		/// <summary>
		/// Calculates the imaginary-part of the anomalous scattering factor 
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Imaginary-part of anomalous scattering factor</returns> 
		double Fii(int Z, double E);

		// Kissel Photoelectric cross sections
		/// <summary>
		/// Calculates the total photoelectric absorption cross section using Kissel partial photoelectric cross sections.
		/// </summary>
		/// <param name="Z">Atomic number of the element</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (cm2/g)</returns>
		double CS_Photo_Total(int Z, double E);

		/// <summary>
		/// Calculates the total photoelectric absorption cross section using Kissel partial photoelectric cross sections.
		/// </summary>
		/// <param name="Z">Atomic number of the element</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns>
		double CSb_Photo_Total(int Z, double E);

		/// <summary>
		/// Calculates the partial photoelectric absorption cross section using Kissel partial photoelectric cross sections.
		/// </summary>
		/// <param name="Z">Atomic number of the element</param>
		/// <param name="shell">Atomic shell ID</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (cm2/g)</returns>
		double CS_Photo_Partial(int Z, int shell, double E);

		/// <summary>
		/// Calculates the partial photoelectric absorption cross section using Kissel partial photoelectric cross sections.
		/// </summary>
		/// <param name="Z">Atomic number of the element</param>
		/// <param name="shell">Atomic shell ID</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns>
		double CSb_Photo_Partial(int Z, int shell, double E);

		// XRF cross sections using Kissel partial photoelectric cross sections
		/// <summary>
		/// Calculates the fluorescent line cross section using Kissel partial photoelectric cross sections   
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="line">Atomic line ID</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (cm2/g)</returns> 
		double CS_FluorLine_Kissel(int Z, int line, double E); 

		/// <summary>
		/// Calculates the fluorescent line cross section using Kissel partial photoelectric cross sections   
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="line">Atomic line ID</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns> 
		double CSb_FluorLine_Kissel(int Z, int line, double E); 

		// Total cross sections (photoionization + Rayleigh + Compton) using Kissel total photoelectric cross sections
		/// <summary>
		/// Calculates the total cross section using Kissel partial photoelectric cross sections.
		/// </summary>
		/// <param name="Z">Atomic number of the element</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (cm2/g)</returns>
		double CS_Total_Kissel(int Z, double E); 

		// Total cross sections (photoionization + Rayleigh + Compton) using Kissel total photoelectric cross sections
		/// <summary>
		/// Calculates the total cross section using Kissel partial photoelectric cross sections.
		/// </summary>
		/// <param name="Z">Atomic number of the element</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns>
		double CSb_Total_Kissel(int Z, double E); 

		/// <summary>
		/// Calculates the fluorescent line cross section including cascade effects.  
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="line">Atomic line ID</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (cm2/g)</returns> 
		double CS_FluorLine_Kissel_Cascade(int Z, int line, double E); 

		/// <summary>
		/// Calculates the fluorescent line cross section including cascade effects.  
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="line">Atomic line ID</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns> 
		double CSb_FluorLine_Kissel_Cascade(int Z, int line, double E);

		/// <summary>
		/// Calculates the fluorescent line cross section with non-radiative cascade effects.  
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="line">Atomic line ID</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (cm2/g)</returns>
		double CS_FluorLine_Kissel_Nonradiative_Cascade(int Z, int line, double E);

		/// <summary>
		/// Calculates the fluorescent line cross section with non-radiative cascade effects.  
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="line">Atomic line ID</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns>
		double CSb_FluorLine_Kissel_Nonradiative_Cascade(int Z, int line, double E);

		/// <summary>
		/// Calculates the fluorescent line cross section with radiative cascade effects.  
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="line">Atomic line ID</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (cm2/g)</returns>
		double CS_FluorLine_Kissel_Radiative_Cascade(int Z, int line, double E);

		/// <summary>
		/// Calculates the fluorescent line cross section with non-radiative cascade effects.  
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="line">Atomic line ID</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns>
		double CSb_FluorLine_Kissel_Radiative_Cascade(int Z, int line, double E);

		/// <summary>
		/// Calculates the fluorescent line cross section without cascade effects.  
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="line">Atomic line ID</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (cm2/g)</returns>
		double CS_FluorLine_Kissel_No_Cascade(int Z, int line, double E);

		/// <summary>
		/// Calculates the fluorescent line cross section without cascade effects.  
		/// </summary>
		/// <param name="Z">Atomic number</param>
		/// <param name="line">Atomic line ID</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns>
		double CSb_FluorLine_Kissel_No_Cascade(int Z, int line, double E);

		//Cross Section functions using the compound parser
		/// <summary>
		/// Calculates the total cross section of a compound.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (cm2/g)</returns>
		double CS_Total_CP(String^ compound, double E);
		
		/// <summary>
		/// Calculates the photoelectric absorption cross section of a compound.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (cm2/g)</returns>
		double CS_Photo_CP(String^ compound, double E);

		/// <summary>
		/// Calculates the Rayleigh scattering cross section of a compound.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (cm2/g)</returns>
		double CS_Rayl_CP(String^ compound, double E);
		
		/// <summary>
		/// Calculates the Compton scattering cross section of a compound.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (cm2/g)</returns>
		double CS_Compt_CP(String^ compound, double E); 
		
		/// <summary>
		/// Calculates the total cross section of a compound.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns>
		double CSb_Total_CP(String^ compound, double E);

		/// <summary>
		/// Calculates the photoelectric absorption cross section of a compound.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns>
		double CSb_Photo_CP(String^ compound, double E);

		/// <summary>
		/// Calculates the Rayleigh scattering cross section of a compound.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns>
		double CSb_Rayl_CP(String^ compound, double E);
		
		/// <summary>
		/// Calculates the Compton scattering cross section of a compound.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns>
		double CSb_Compt_CP(String^ compound, double E); 
		
		/// <summary>
		/// Calculates the Rayleigh differential scattering cross section of a compound.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <returns>Cross section (cm2/g/sterad)</returns>
		double DCS_Rayl_CP(String^ compound, double E, double theta);
		
		/// <summary>
		/// Calculates the Compton differential scattering cross section of a compound.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <returns>Cross section (cm2/g/sterad)</returns>		
		double DCS_Compt_CP(String^ compound, double E, double theta);
		
		/// <summary>
		/// Calculates the Rayleigh differential scattering cross section of a compound.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <returns>Cross section (barn/sterad)</returns>
		double DCSb_Rayl_CP(String^ compound, double E, double theta);
		
		/// <summary>
		/// Calculates the Compton differential scattering cross section of a compound.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <returns>Cross section (barn/sterad)</returns>
		double DCSb_Compt_CP(String^ compound, double E, double theta);
		
		/// <summary>
		/// Calculates the Rayleigh differential scattering cross section for polarized beam for a compound.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <param name="phi">Scattering azimuthal angle (rad)</param>
		/// <returns>Cross section (cm2/g/sterad)</returns>
		double DCSP_Rayl_CP(String^ compound, double E, double theta, double phi);

		/// <summary>
		/// Calculates the Compton differential scattering cross section for polarized beam for a compound.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <param name="phi">Scattering azimuthal angle (rad)</param>
		/// <returns>Cross section (cm2/g/sterad)</returns>
		double DCSP_Compt_CP(String^ compound, double E, double theta, double phi);

		/// <summary>
		/// Calculates the Rayleigh differential scattering cross section for polarized beam for a compound.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <param name="phi">Scattering azimuthal angle (rad)</param>
		/// <returns>Cross section (barn/sterad)</returns>
		double DCSPb_Rayl_CP(String^ compound, double E, double theta, double phi);

		/// <summary>
		/// Calculates the Compton differential scattering cross section for polarized beam for a compound.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <param name="theta">Scattering polar angle (rad)</param>
		/// <param name="phi">Scattering azimuthal angle (rad)</param>
		/// <returns>Cross section (barn/sterad)</returns>
		double DCSPb_Compt_CP(String^ compound, double E, double theta, double phi);
	
		/// <summary>
		/// Calculates the total photoelectric absorption cross section for a compound.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (cm2/g)</returns>		
		double CS_Photo_Total_CP(String^ compound, double E);

		/// <summary>
		/// Calculates the total photoelectric absorption cross section for a compound.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns>	
		double CSb_Photo_Total_CP(String^ compound, double E);

		/// <summary>
		/// Calculates the total photoelectric absorption cross section for a compound
		/// using Kissel partial photoelectric cross sections.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (cm2/g)</returns>
		double CS_Total_Kissel_CP(String^ compound, double E);

		/// <summary>
		/// Calculates the total photoelectric absorption cross section for a compound
		/// using Kissel partial photoelectric cross sections.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Cross section (barn)</returns>
		double CSb_Total_Kissel_CP(String^ compound, double E); 

		//Refractive indices functions
		/// <summary>
		/// Calculates the real part of the anomalous scattering factor.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Real part of refractive index (electrons)</returns>
		double Refractive_Index_Re(String^ compound, double E, double density);
		
		/// <summary>
		/// Calculates the imaginary part of the anomalous scattering factor.
		/// </summary>
		/// <param name="compound">Chemical formula of the compound</param>
		/// <param name="E">Energy (keV)</param>
		/// <returns>Imaginary part of refractive index (electrons)</returns>
		double Refractive_Index_Im(String^ compound, double E, double density);

		/// <summary>
		/// Calculates the electron configuration according to Kissel.
		/// </summary>
		/// <param name="Z">Atomic number of the element</param>
		/// <param name="shell">Atomic shell ID</param>
		/// <returns>Electron configuration</returns> 
		double ElectronConfig(int Z, int shell);

		//ComptonProfiles
		/// <summary>
		/// Calculates the total Compton scattering profile.
		/// </summary>
		/// <param name="Z">Atomic number of the element</param>
		/// <param name="pz">Momentum</param>
		/// <returns>Compton profile</returns> 
		double ComptonProfile(int Z, double pz);

		/// <summary>
		/// Calculates the sub-shell Compton scattering profile.
		/// </summary>
		/// <param name="Z">Atomic number of the element</param>
		/// <param name="shell">Atomic shell ID</param>
		/// <param name="pz">Momentum</param>
		/// <returns>Compton profile</returns> 
		double ComptonProfile_Partial(int Z, int shell, double pz);

		/// <summary>Calculates the atomic level width. </summary>
		/// <param name="Z">Atomic number of the element. </param>
		/// <param name="shell">Atomic shell ID. </param>
		/// <returns>Level width (keV)</returns>
		double AtomicLevelWidth(int Z, int shell);

		/// <summary>Calculates the Auger non-radiative rate. </summary>
		/// <param name="Z">Atomic number of the element. </param>
		/// <param name="auger_trans">Value identifying initial ionized shell and two resulting ejected electrons</param>
		/// <returns>Non-radiative rate</returns>
		double AugerRate(int Z, int auger_trans);

		/// <summary>
		/// Returns the Siegbahn line name corresponding to the specified IUPAC name.
		/// </summary>
		/// <param name="name">IUPAC line name</param>
		/// <returns>Siegbahn line name </returns> 
		System::String ^IUPACToSiegbahnLineName(System::String ^name);

		/// <summary>
		/// Returns IUPAC line name corresponding to the specified Siegbahn name.
		/// </summary>
		/// <param name="name">Siegbahn line name</param>
		/// <returns>IUPAC line name </returns> 
		System::String ^SiegbahnToIUPACLineName(System::String ^name);

		/// <summary>
		/// Returns the energy of the specified fluorescent line string.
		/// </summary>
		/// <param name="lineName">String containing the element and emission line, e.g. Cu Ka1</param>
		/// <returns>Fluorescent line energy (keV)</returns> 
		double LineEnergyFromName(System::String ^lineName);

		/// <summary>
		/// Returns the atomic number and line ID of the specified fluorescent line string.
		/// </summary>
		/// <param name="elementLine">String containing the element and emission line, e.g. Cu Ka1</param>
		/// <param name="Z">Atomic number</param>
		/// <param name="line">Emission line ID</param>
		void ElementAndLineFromName(System::String ^elementLine, int %Z, int %line);

		/// <summary>
		/// Returns the line ID of the specified emission line name.
		/// </summary>
		/// <param name="name">String containing the emission line name, e.g. Ka1</param>
		/// <returns>ID of the emission line</returns> 
		int SiegbahnLineIndex(System::String ^name);

		/// <summary>
		/// Returns the atomic number from the specified element name.
		/// </summary>
		/// <param name="name">Element name, e.g. Cu</param>
		/// <returns>Atomic number</returns> 
		int AtomicNumber(System::String ^name);

		/// <summary>
		/// Calculates the energy of the escape peak for a Si detector.
		/// </summary>
		/// <param name="energy">Energy of the incident X-ray peak (keV)</param>
		/// <returns>Energy of the escape peak (keV)</returns> 
		double SiEscapeEnergy(double energy);

		/// <summary>
		/// Calculates the fraction of photons in the escape peak for a Si detector.
		/// </summary>
		/// <param name="energy">Energy of the incident X-ray peak (keV)</param>
		/// <returns>Fraction of incident photons in the escape peak</returns> 
		double SiEscapeFraction(double energy);;
	};

}
