//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Dialogs.hpp>

#define tab_char 9
#define newLine_char 10
#define quot_char 34
#define comma_char 44

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPageControl *TabSheet_studentsInfo;
	TTabSheet *TabSheet_Student;
	TStringGrid *StringGrid_students;
	TTabSheet *TabSheet_classList;
	TStringGrid *StringGrid_classList;
	TTabSheet *TabSheet_dataFile;
	TMemo *Memo_dataFile;
	TPanel *Panel3;
	TOpenDialog *OpenDialog_loadDataFile;
	TSaveDialog *SaveDialog_downloadClassList;
	TTabSheet *TabSheet_log;
	TMemo *Memo_log;
	TPanel *Panel4;
	TCheckBox *CheckBox_term1;
	TCheckBox *CheckBox_term2;
	TButton *Button_scanDataFile;
	TButton *Button_generateClassList;
	TButton *Button_downloadClassList;
	TButton *Button_loadDataFile;
	TStaticText *StaticText1;
	TStaticText *StaticText2;
	TStaticText *StaticText3;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Button_loadDataFileClick(TObject *Sender);
	void __fastcall CheckBox_term1Click(TObject *Sender);
	void __fastcall CheckBox_term2Click(TObject *Sender);
	void __fastcall Button_scanDataFileClick(TObject *Sender);
   //	void __fastcall Button_saveDataFileClick(TObject *Sender);
	void __fastcall Button_generateClassListClick(TObject *Sender);
	void __fastcall Button_downloadClassListClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
    int selTermNum;
	__fastcall TForm1(TComponent* Owner);
	String __fastcall ScanString(String ss, int *xp,char endch);
	String __fastcall ScanCourse(String ss);
	bool __fastcall ScanCourseEnd(String ss, int *xp);



};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
