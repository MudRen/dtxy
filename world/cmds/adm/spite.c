// xgrep.c 
// write by JackyBoy@CuteRabbit Studio for SDXL & CCTX 1999/6/1
// Ϊ�˱���ݹ�̫��벻Ҫ���ý��뼶�𳬹�16��. JackyBoy
inherit F_CLEAN_UP;
int help();

int sort(string a,string b);
int main(object me, string arg)
{
	string *file;
	string str;
	int i;
	str="";
//        if (!arg) return help();
	file=sort_array(explode(read_file("/data/chinese.o"),","),(:sort:));
	for (i=0;i<sizeof(file);i++)
	  str+=file[i]+",\n";
	if (!write_file("/data/chinese.new",str,1))
	  return notify_fail("ʧ��!\n");
	write("�ɹ�!\n");
	seteuid(geteuid(me));
	return 1;
}

int sort(string a,string b)
{
	if (a<b) return -1;
	return 1;
}


int help()
{
  write(@HELP

X grep ���� v0.1  Write By JackyBoy@CuteRabbit for CCTX & SDXL 1999/6/1
��ҳ��http://mud.yn.cninfo.net/jackyboy
�ʼ���jackyboy@126.com


ָ���ʽ : xgrep [-d[0-15]] ·�� ��Ҫ�������ַ���
��ָ���������ָ��(����Ŀ¼��������ͨ�����ָ��)������Ŀ¼��Ѱ�Һ���Ҫ
�������ַ������ļ���������λ����ʾ������
ע�⣬Ĭ�Ͻ�������ǰĿ¼��
��֪BUG��
�Զ������ļ������������������Ϊ��ֹ��'\0'���õ�һ��string�
HELP
    );
    return 1;
}
