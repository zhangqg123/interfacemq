#include "stdafx.h" 
#include "IniFile.h" 
#include "locale.h"
#ifdef _DEBUG 
#undef THIS_FILE 
static char THIS_FILE[]=__FILE__; 
#define new DEBUG_NEW 
#endif 

////////////////////////////////////////////////////////////////////// 
// Construction/Destruction 
////////////////////////////////////////////////////////////////////// 

CIniFile::CIniFile() 
{ 
    m_sFileName = "ini.ini"; 
	//FileContainer.SetSize(100,1);
} 

CIniFile::~CIniFile() 
{ 
    if(FileContainer.GetSize() > 0) 
    { 
        FileContainer.RemoveAll(); 
    } 
} 

//�����ļ�ȫ·��
void CIniFile::SetFileName(CString FileName) 
{ 
    m_sFileName = FileName; 
} 

void CIniFile::SetInt(CString Section, CString Item, int Value) 
{ 
    CString strtemp; 
	strtemp.Format(L"%d",Value); 
    //���浽FileContainer 
    WriteFileString(Section, Item, strtemp); 
    //���浽ini�ļ� 
    WriteIniFile(); 
} 

void CIniFile::GetAllSectionName(CStringList &list)
{
	CString csLine;
	bFileExist = IniFile.Open(m_sFileName,CFile::modeRead);
	if(!bFileExist)
	{
		return;
	}
	while(IniFile.ReadString(csLine))
	{
		if(csLine[0] != '[' || csLine[csLine.GetLength()-1] != ']')
		{
			continue;
		}
#ifdef UNICODE
		AcsiToUnicode(csLine);
#endif
		csLine = csLine.Left(csLine.Find(L"]"));//ȥ��]�ұ� 
		csLine = csLine.Right(csLine.GetLength() - csLine.Find(L"[")-1);//ȥ��[��� 
		
		if(list.IsEmpty())
		{
			list.AddHead(csLine);
		}
		else
		{
			list.AddTail(csLine);
		}
	}
	IniFile.Close();
}

void CIniFile::SetString(CString Section, CString Item, CString Value) 
{ 
    //���浽FileContainer 
    WriteFileString(Section, Item, Value); 
    //���浽ini�ļ� 
    WriteIniFile(); 
} 

CString CIniFile::GetString(CString Section, CString Item) 
{ 
    return GetFileString(Section, Item); 
} 

int CIniFile::GetInt(CString Section, CString Item) 
{ 
   //CString strtemp; 
   // strtemp.Format("%d",Value); 
	//  return atoi(GetFileString(Section, Item, strtemp)); 
    return _ttoi(GetFileString(Section, Item)); 
} 

BOOL CIniFile::ReadIniFile() 
{ 
	bFileExist = IniFile.Open(m_sFileName, CFile::modeRead); 

	if(!bFileExist) 
	{ 
		return FALSE; 
	} 

	CString strline; 
	FileContainer.RemoveAll(); 
	
    //��IniFile�ļ����ݶ���FileContainer 
	while(IniFile.ReadString(strline)) 
	{ 
#ifdef _UNICODE
		AcsiToUnicode(strline);
#endif
		FileContainer.Add(strline); 
	} 

    IniFile.Close(); 
    return TRUE; 
} 

BOOL CIniFile::WriteIniFile() 
{ 
    bFileExist = IniFile.Open(m_sFileName, CFile::modeCreate | CFile::modeWrite); //|CFile::modeNoTruncate
	if(!bFileExist) 
		return FALSE; 
	//IniFile.SeekToEnd();
    CString strline; 

    //��FileContainerд��IniFile�ļ� 
    for(int i = 0; i< FileContainer.GetSize(); i++) 
    { 
        strline = FileContainer[i]; 
#ifdef UNICODE
		char* old_locale = _strdup( setlocale(LC_CTYPE,NULL) );
		setlocale( LC_CTYPE, "chs");//�趨
		IniFile.WriteString(strline + L"\n");//����д��
		setlocale( LC_CTYPE, old_locale );
		free( old_locale );//��ԭ�����趨 
#else
		IniFile.WriteString(strline + L"\n");
#endif
		 
    } 

    IniFile.Close(); 

    return bFileExist; 
} 


CString CIniFile::GetFileString(CString Section, CString Item) 
{ 
	CString csValue = L"0";

    bFileExist = ReadIniFile();//���ļ� 
    if(bFileExist == FALSE) 
        return csValue;//�ļ��򿪳�����ļ�Ϊ�գ�����Ĭ��ֵ 
	int i = 0; 
	int iFileLines = FileContainer.GetSize(); 
	CString strline,str; 

    while(i < iFileLines) 
    { 
        strline = FileContainer.GetAt(i++); 

        strline.TrimLeft(); 
        if(strline.GetAt(0)=='[')//����Section����һ������Ϊ[ 
        { 
            str = strline.Left(strline.Find(L"]"));//ȥ��]�ұ� 
            str = str.Right(str.GetLength() - str.Find(L"[")-1);//ȥ��[��� 

            str.TrimLeft(); 
            str.TrimRight(); 

            if(Section == str)//�ҵ�Section 
            { 
                while(i < iFileLines) 
                { 
                    strline = FileContainer.GetAt(i++); 
                    strline.TrimLeft(); 

                    if(strline.GetAt(0) == '[') 
                        return csValue;//���������һ��[]�����Ҳ���,����Ĭ��ֵ 
                     
                    str = strline.Left(strline.Find(L"="));//ȥ��=�ұ� 

                    str.TrimLeft(); 
                    str.TrimRight(); 

                    if(Item == str)//�ҵ�Item 
                    { 
                        str = strline.Right(strline.GetLength() - strline.Find(L"=") - 1);//ȥ��=��� 

                        str.TrimLeft(); 
                        str.TrimRight(); 

                        return str; 
                    } 
                } 
                return csValue;//�Ҳ���,����Ĭ��ֵ 
            } 

        } 

    } 
    return csValue;//�Ҳ���,����Ĭ��ֵ 
} 

void CIniFile::WriteFileString(CString Section, CString Item, CString Value) 
{ 
    int i = 0; 

	ReadIniFile();

    int iFileLines = FileContainer.GetSize(); 

    CString strline,str; 

    while(i < iFileLines) 
    { 
        strline = FileContainer.GetAt(i++); 

        strline.TrimLeft(); 
        if(strline.GetAt(0) == '[')//����Section����һ������Ϊ[ 
        { 
            str = strline.Left(strline.Find(L"]"));//ȥ��]�ұ� 
            str = str.Right(str.GetLength()-str.Find(L"[") - 1);//ȥ��[��� 

            str.TrimLeft(); 
            str.TrimRight(); 

            if(Section == str)//�ҵ�Section 
            { 
                while(i < iFileLines) 
                { 
                    strline = FileContainer.GetAt(i++); 
                    strline.TrimLeft(); 

                    if(strline.GetAt(0) == '[')//���������һ��[]�����Ҳ���Item 
                    { 
                        break; 
                    } 
                     
                    str = strline.Left(strline.Find(L"="));//ȥ��=�ұ� 

                    str.TrimLeft(); 
                    str.TrimRight(); 

                    if(Item == str)//�ҵ�Item 
                    { 
                        strline = Item + "=" + Value; 
                        FileContainer[i-1] = strline; 
                        return; 
                    } 
                } 
                //�Ҳ���Item 
                strline = Item + "=" + Value; 
                FileContainer.InsertAt(i-1, strline); 
                return; 
            } 
        } 
    } 
    //�Ҳ���Section 
    //ֱ����������Section��Item��Value 
    FileContainer.Add(L"[" + Section + L"]"); 
    FileContainer.Add(Item + "=" + Value); 
    return; 
} 

BOOL CIniFile::AcsiToUnicode(CString &str)
{
	char *szBuf = new char[ str.GetLength()+1]; //����Ҫ��1


	for (int i = 0 ; i < str.GetLength(); i++)
	{
		szBuf[i] = (CHAR)str.GetAt(i);
	}  
	szBuf[str.GetLength()]='\0';   //�������Ҫ���ϣ�������ڽ�βƬ��ʾһ��"��"�֡�
	// USES_CONVERSION;
	//char * sz=W2A(str.GetBuffer());  //��Щ�����Ҷ��Թ������еġ�
	BOOL bok= CharToUnicode(szBuf , str);
	delete []szBuf;
	return bok;
}

//�˺�����ԭ�����õġ�����Ҫ�κθ���
/////////////////////////////////////////////////////////////////////////////////////////
// ��Char���ַ�ת��ΪUnicode�ַ�
int CIniFile::CharToUnicode(char *pchIn, CString &pstrOut)
{
	int nLen;
	WCHAR *ptch;

	if(pchIn == NULL)
	{
		return 0;
	}
	nLen = MultiByteToWideChar(CP_ACP, 0, pchIn, -1, NULL, 0);//ȡ�����軺��Ķ���
	ptch = new WCHAR[nLen];//���뻺��ռ�
	MultiByteToWideChar(CP_ACP, 0, pchIn, -1, ptch, nLen);//ת��
	//pstrOut->Format(_T("%s"), ptch);
	pstrOut = ptch;
	delete [] ptch;
	return nLen;
}