//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
TabSheet_studentsInfo->Align=alClient;
  StringGrid_students->Cells[0][0]="ID";
  StringGrid_students->Cells[1][0]="Name";
  StringGrid_students->Cells[2][0]="Unit #";
  StringGrid_students->Cells[3][0]="Faculty";
  StringGrid_students->Cells[4][0]="Email";
  StringGrid_students->Cells[5][0]="Class 1";
  StringGrid_students->Cells[6][0]="Class 2";
  StringGrid_students->Cells[7][0]="Class 3";
  StringGrid_students->Cells[8][0]="Class 4";
  StringGrid_students->Cells[9][0]="Class 5";
  StringGrid_students->Cells[10][0]="Class 6";
  StringGrid_students->Cells[11][0]="Class 7";
  StringGrid_students->Cells[12][0]="Class 8";
  StringGrid_students->Cells[13][0]="Class 9";
  StringGrid_students->Cells[14][0]="Class 10";

}
//---------------------------------------------------------------------------




void __fastcall TForm1::Button_loadDataFileClick(TObject *Sender)
{
TabSheet_studentsInfo->ActivePage = TabSheet_dataFile;
String xs;
//OpenDialog_loadDataFile->InitialDir=xSlave_Application_Dir;
OpenDialog_loadDataFile->FileName="*.csv";
OpenDialog_loadDataFile->Filter="dataFile(*.csv)|*.CSV|dataTxtFile(*.txt)|*.TXT";

if(OpenDialog_loadDataFile->Execute())
		 {
		   xs=OpenDialog_loadDataFile->FileName;
		   Memo_dataFile->Lines->LoadFromFile(xs);
		   }

}

//---------------------------------------------------------------------------

void __fastcall TForm1::Button_scanDataFileClick(TObject *Sender)
{
TabSheet_studentsInfo->ActivePage = TabSheet_Student;
	String temp;
	String termNum;
	String tempBuffer;
	String CurrentLineStr;
	String tab_str=" ";
	tab_str[1]=tab_char;

	String quot_str=" ";
	quot_str[1]=quot_char;
	int done=0; //keep track of when complete one student's info; when encounter ' " '
	int lineNum=0;
	int lineIndex=0;
	int count;
	int row=1;
	int repeat=0;


		while(lineNum < Memo_dataFile->Lines->Count){
				done=0;

				Memo_log->Lines->Add("next student ");
				StringGrid_students->Cells[0][row]= IntToStr(row); //student ID
				if( Memo_dataFile->Lines->Strings[lineNum] == "")
					lineNum++;
				for(count =1; count < 5; count++){  //personal info
					StringGrid_students->Cells[count][row]=
					ScanString(Memo_dataFile->Lines->Strings[lineNum], &lineIndex, ',');

				}
				lineNum++;



				while(!done ){
					lineIndex=0;
					CurrentLineStr = Memo_dataFile->Lines->Strings[lineNum]; Memo_log->Lines->Add("line#"+IntToStr(lineNum)+":"+CurrentLineStr);

					//check if it is valid line with course info
					temp = ScanString(CurrentLineStr, &lineIndex, tab_char);

					if(CurrentLineStr.Pos(tab_str) > 0 && temp.Length() <= 4 && temp != "" )
					{

					   //Course title
						temp = ScanString(CurrentLineStr, &lineIndex, tab_char); Memo_log->Lines->Add(tempBuffer);
						tempBuffer=ScanCourse(temp);

						//skip class location
						temp = ScanString(CurrentLineStr, &lineIndex, tab_char);

						String ss =  ScanString(CurrentLineStr, &lineIndex, tab_char);

						termNum=ss.Trim();
						Memo_log->Lines->Add(termNum+"=?="+selTermNum);

						if(StrToInt(termNum) == selTermNum){
						   repeat=0;
						   for(int i =5; i<count && i<StringGrid_students->ColCount; i++){ //check if already inputted current class
							 if(StringGrid_students->Cells[i][row].Pos(tempBuffer) > 0) {
								repeat = 1; Memo_log->Lines->Add("Repeated Class:" + tempBuffer);
							 }
						   }

						   if (!repeat && tempBuffer != "" && tempBuffer.Length() >= 3) {

							 if(count>StringGrid_students->ColCount){
								StringGrid_students->ColCount++;
							 }
							 StringGrid_students->Cells[count][row]=tempBuffer;
							 Memo_log->Lines->Add("added class:" + tempBuffer);
							 count++;

						   }
						   else Memo_log->Lines->Add("found unuseful line");

						   tempBuffer = ""; //empty buffer
						}
						else Memo_log->Lines->Add("found unuseful line");
					 }

					if(Memo_dataFile->Lines->Strings[lineNum].Pos(quot_str)>0){  //  if line contains "
						done = 1;  Memo_log->Lines->Add("arrived at end of current student");
					}
					lineNum++;

					lineIndex =0;


			   }
			   //while for current student

			StringGrid_students->RowCount++;
			row++;


	 }  // while for all lines
}







 //---------------------------------------------------------------------------



void __fastcall TForm1::CheckBox_term1Click(TObject *Sender)
{

if (CheckBox_term1->Checked) {
	selTermNum = 1;
	CheckBox_term2->Checked=false;
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox_term2Click(TObject *Sender)
{
if (CheckBox_term2->Checked) {
	selTermNum = 2;
	CheckBox_term1->Checked=false;
}

}
//---------------------------------------------------------------------------


String __fastcall TForm1::ScanString(String ss, int *xp,char endch)
{
  int xl;
  String xs;

  xl=ss.Length();
  xs="";
  (*xp)++;
  while (
		 ((*xp)<=xl)    &&
		 (ss[*xp]!=endch)
		)
   {
	 xs=xs+ss.SubString(*xp,1);
     (*xp)++;
   }

  return(xs);
}
//---------------------------------------------------------------------------


String __fastcall TForm1::ScanCourse(String ss)
{
  int xl;
  String xs;
  int flag=0;

  xl=ss.Length();
  xs="";

 int i=1;
  while (
		 ((i<=xl)    &&
		 ss[i]!=' ') ||
		 !flag
		)
   {
	 if(ss[i]== ' ')
		flag = 1;
	 xs=xs+ss.SubString(i,1);
	 i++;
   }

  return(xs);

}

 //---------------------------------------------------------------------------


//Scan to the end of string and see if there is a "
  bool __fastcall TForm1::ScanCourseEnd(String ss, int *xp)
{
  int xl;
  String xs;

  (*xp)++;
  xl=ss.Length();
  xs="";
  while ( ((*xp)<=xl) && ss[*xp]!= newLine_char)
   {
	 if(ss[*xp]== '"')
		return true;
	 (*xp)++;
   }

  return false;
}

//---------------------------------------------------------------------------

/*
void __fastcall TForm1::Button_saveDataFileClick(TObject *Sender)
{

SaveDialog_saveDataFile->FileName="*.csv";
SaveDialog_saveDataFile->Filter="dataFile(*.csv)|*.CSV|dataTxtFile(*.txt)|*.TXT";

if(SaveDialog_saveDataFile->Execute())
		 {
		   xs=SaveDialog_saveDataFile->FileName;
		   Memo_dataFile->Lines->SaveToFile(xs);

		   }
			  }
}
*/
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_generateClassListClick(TObject *Sender)
{
TabSheet_studentsInfo->ActivePage = TabSheet_classList;
	int stuRow, stuCol;
	int classRow, classCol;
	int numClass=0;
	int numStudents;
	String currentClass;
	String stuName;
	String stuEmail;
	int foundClass =0;
	int firstEntry =0;

	for(stuRow=1; stuRow < StringGrid_students->RowCount; stuRow++){ //transverse through each student
		for(stuCol=5; stuCol < StringGrid_students->ColCount && StringGrid_students->Cells[stuCol][stuRow] != ""; stuCol++){
			foundClass=0;
			currentClass = StringGrid_students->Cells[stuCol][stuRow];
			stuName = StringGrid_students->Cells[1][stuRow];
			stuEmail =  StringGrid_students->Cells[4][stuRow];

			for(classRow =0; classRow <= numClass*2 && foundClass != 1; classRow = classRow+2){ //cycle through current classes in list

				if (StringGrid_classList->Cells[0][classRow].Pos(currentClass) > 0) {//if class list already already contains current class
					numStudents = StrToInt(StringGrid_classList->Cells[1][classRow]);
					StringGrid_classList->Cells[numStudents+2][classRow] = stuName;
					StringGrid_classList->Cells[numStudents+2][classRow+1] = stuEmail;
					foundClass = 1;
                    StringGrid_classList->Cells[1][classRow]=IntToStr(numStudents+1);
				}

			}//every class

			if(!foundClass){ //if class is NOT in list
				if(firstEntry)
					StringGrid_classList->RowCount = StringGrid_classList->RowCount + 2; //add two rows for new class
				int lastRow = StringGrid_classList->RowCount;
				numClass++;
				StringGrid_classList->Cells[0][lastRow-1] = currentClass;
				StringGrid_classList->Cells[1][lastRow-1] = "1";
				StringGrid_classList->Cells[2][lastRow-1] = stuName;
				StringGrid_classList->Cells[2][lastRow] = stuEmail;
                firstEntry=1;


			}


		} //every class

	} //every student
	StringGrid_classList->RowCount++ ;


}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_downloadClassListClick(TObject *Sender)
{
	int row;
	int col;
	int endFlag;

	String strBuffer;
	String xs;

	//clear memory log
	Memo_log->Lines->Clear();

	//copy Class List to Memo
	for( row =0; row<= StringGrid_classList->RowCount; row++){
		strBuffer = "";

		endFlag=0;
		if (row%2 == 0) {//odd rows contain class name and class number
			for(col=0; col <= StringGrid_classList->ColCount && endFlag != 1; col++){
				if( StringGrid_classList->Cells[col][row] == "")
					endFlag=1;
				else
					strBuffer = strBuffer + "," + StringGrid_classList->Cells[col][row];

			}

			Memo_log->Lines->Add(strBuffer.SubString(2,strBuffer.Length()));
		}

		else
		{
			strBuffer = strBuffer + ","; //to allign
			for(col=2; col <= StringGrid_classList->ColCount && endFlag != 1; col++){
				if( StringGrid_classList->Cells[col][row] == "")
					endFlag=1;
				else
					strBuffer = strBuffer + "," + StringGrid_classList->Cells[col][row];
			}
			strBuffer = strBuffer + '\n';
			Memo_log->Lines->Add(strBuffer);

		}


	}
		//Save Memo as file
	SaveDialog_downloadClassList->FileName="*.csv";
	SaveDialog_downloadClassList->Filter="dataFile(*.csv)|*.CSV|dataTxtFile(*.txt)|*.TXT";

	if(SaveDialog_downloadClassList->Execute())
		 {
		   xs=SaveDialog_downloadClassList->FileName;
		   Memo_log->Lines->SaveToFile(xs);

		   }





}


//---------------------------------------------------------------------------



