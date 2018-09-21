unit xrltest;

{$mode objfpc}
{$h+}


interface

uses custapp, Classes, SysUtils, fpcunit, testreport, testregistry;

type
	TestRunner = class(TCustomApplication)
	private
		FXMLResultsWriter: TXMLResultsWriter;
	protected
		procedure DoRun ; Override;
	public
		constructor Create(AOwner: TComponent); override;
		destructor Destroy; override;
	end;

implementation

constructor TestRunner.Create(AOwner: TComponent);
begin
	inherited Create(AOwner);
	FXMLResultsWriter := TXMLResultsWriter.Create;
end;

destructor TestRunner.Destroy;
begin
	FXMLResultsWriter.Free;
end;

procedure TestRunner.DoRun;
var
	testResult: TTestResult;
begin
	testResult := TTestResult.Create;
	try
		testResult.AddListener(FXMLResultsWriter);
		GetTestRegistry.Run(testResult);
		FXMLResultsWriter.WriteResult(testResult);
	finally
		testResult.Free;
	end;
	Terminate;
end;
end.
