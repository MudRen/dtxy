#include <ansi.h>
inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }
 int email_flag,icq_flag,webpage_flag;
int main(object me, string arg)
{
        object link;
       
        if( link = me->query_temp("link_ob") ) {
        	email_flag = link->query("email")?1:0;
        	//icq_flag = link->query("icq")?1:0;
        	//webpage_flag = link->query("webpage")?1:0;
        	if(email_flag ==0) link->set("email","");
        	//if(icq_flag ==0) link->set("icq","");
        	//if(webpage_flag ==0) link->set("webpage","");
                write("���ĵ����ʼ�"+(email_flag?(" [" + link->query("email") + "]��"):"��"));
                input_to("get_email", link);
                return 1;
        }
        return 0;
}
string rp_color(string arg)
{
     if (!arg) return "";
        arg = replace_string(arg, "$BLK$", BLK);
        arg = replace_string(arg, "$RED$", RED);
        arg = replace_string(arg, "$GRN$", GRN);
        arg = replace_string(arg, "$YEL$", YEL);
        arg = replace_string(arg, "$BLU$", BLU);
        arg = replace_string(arg, "$MAG$", MAG);
        arg = replace_string(arg, "$CYN$", CYN);
        arg = replace_string(arg, "$WHT$", WHT);
        arg = replace_string(arg, "$HIR$", HIR);
        arg = replace_string(arg, "$HIG$", HIG);
        arg = replace_string(arg, "$HIY$", HIY);
        arg = replace_string(arg, "$HIB$", HIB);
        arg = replace_string(arg, "$HIM$", HIM);
        arg = replace_string(arg, "$HIC$", HIC);
        arg = replace_string(arg, "$HIW$", HIW);
        arg = replace_string(arg, "$BLINK$", BLINK);
        arg = replace_string(arg, "$NOR$", NOR);
        return arg+NOR;
}

void get_email(string new_email, object link)
{
        if( new_email != ""&&strlen(new_email) < 50)
                link->set("email", new_email);
 }
int help(object me)
{
write(@HELP
ָ���ʽ : e_mail

  ��; : �����޸���ĸ������䡣
  �÷� ��ϵͳ������ʾ������:
       �����ʼ���ַ��  ��Ҫ����ʦ�һ����룬����д��ȷ��E_mail���µ�����ᷢ�����ע�������С���       
������Ϻ�һ��Ҫ save ���������á�
HELP
     );
     return 1;
}


