// used for only by admin
// by canoe
#include <login.h>;
inherit F_CLEAN_UP;

void create()
{
        seteuid(getuid());
}

int main(object me, string arg)
{
        object ob,link_ob;
        string id,password;
        if(!arg||sscanf(arg,"%s %s",id,password)!=2)
                return notify_fail("�÷�:xsuppwd ID ����ݼ�����\n�˲���������������棬������ȵ��������\n");
        ob=find_player(id);
        if(!ob)
        {
        ob = new(LOGIN_OB);
        ob->set("id",id);
        if( !ob->restore() )
                return notify_fail("û�������ҡ�\n");
        else
                {                                    
           ob->set("super_password",crypt(password,0));
           tell_object(me, "���" + ob->query("id") + "("+ob->query("name")
                + ")����ݼ������Ѿ�����Ϊ��"+password+"��\n");
           log_file( "changesuper_password.log", sprintf("%s %s(%s)�޸���%s(%s)����ݼ�����",
                ctime(time()), me->query("name"), me->query("id"),
                ob->query("name"), ob->query("id")));
           ob->save();
           destruct(ob);
           return 1;
                }
        }
        link_ob=ob->query_temp("link_ob");
        if(link_ob)
        {
                link_ob->set("super_password",crypt(password,0));
 log_file( "changesuper_password.log", sprintf("%s %s(%s)�޸���%s(%s)����ݼ����롣",
               ctime(time()), me->query("name"), me->query("id"),
                ob->query("name"), ob->query("id")));

                link_ob->save();
                tell_object(me, "���" + ob->query("id") + "("+ob->query("name")
                        + ")����ݼ������Ѿ�����Ϊ��"+password+"��\n");
                tell_object(ob,"�����ݼ����뱻�����޸��ˣ���ȥ�� "+me->query("id")+" ���档\n");
                return 1;
        }
        else
                return notify_fail("�����޷������޸ġ�\n");
        return 1;
}


int help(object me)
{
        write(@HELP
ָ���ʽ : xsuppwd ID �µ���ݼ�����

���ָ������޸���ҵ���ݼ����룬�����ʹ�á�

HELP
    );
    return 1;
}

