// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
 
// /cmds/usr/freeze.c
// FoF 00-5-29
// �����ʺ� 
// last motified by ammy@yszz  12/06/2000
// ������ʦ�����߼�������ҵĲ���

#include <ansi.h>

inherit F_CLEAN_UP;

void create()
{
        seteuid(getuid());
}

int main(object me, string arg)
{
    object ob,link_ob;
    string id,wiz_status;
    int day, hour, freeze_time;
    if(!arg || sscanf(arg,"%s %d day %d hour",id,day,hour) !=3 )       
        return notify_fail("ָ���ʽ��freeze <id> <n> day <n> hour\n");
    arg=lower_case(arg);
    if (!me->id(id)) {
          wiz_status = SECURITY_D->get_status(me);
          if( wiz_status != "(admin)" && wiz_status != "(arch)" && wiz_status != "(wizard)")
	        return notify_fail("ֻ�� (wizard) ���ϵ���ʦ���ܶ����ⶳ������ң�\n");
     }
    if( day < 0 || hour < 0 ) return notify_fail("ʱ�䲻���Ǹ�����\n");
    freeze_time =day*24*60*60 + hour*60*60;
    if(freeze_time > 36*24*60*60 ) return notify_fail("�����ʱ��̫���ˣ�\n");
    freeze_time +=time();
    ob=find_player(id);
    if(!ob)
    {
        ob = new(LOGIN_OB);
        ob->set("id",id);
        if( !ob->restore() )
                return notify_fail("û�������ҡ�\n");
        else
        {
          ob->set("freeze_time",freeze_time);
          tell_object(me,ob->query("id") + "("+ob->query("name")
                + ")���˺��Ѿ����ᡣ�Զ��ⶳ����"+day+"��"+hour+"Сʱ��! \n");
          log_file( "freeze_account.log", sprintf("%s %s(%s)����%s(%s)���˺�!  \n ����ʱ��Ϊ%d��%dСʱ. \n",
                ctime(time()), me->query("name"), me->query("id"),
                ob->query("name"), ob->query("id"),day,hour));
          ob->save();
          destruct(ob);
          return 1;
                }
        }
    if (!wizardp (me)){    
      if( ob->query("last_freeze_account") )
        if( time() - ob->query("last_freeze_account") < 60 )
            return notify_fail("�ʺŶ���ʧ�ܣ���ողŶ�����ʺš�\n");
     }
    // LOGIN_OB Ҫ����Ӧ�ĸĶ�������set("freeze_time", freeze_time)ʧ��
    link_ob = ob->query_temp("link_ob");
    if( link_ob->set("freeze_time", freeze_time) && link_ob->save() ) {
          tell_object(me,ob->query("id") + "("+ob->query("name")
                + ")���˺��Ѿ����ᡣ�Զ��ⶳ����"+day+"��"+hour+"Сʱ��! \n");
          log_file( "freeze_account.log", sprintf("%s %s(%s)����%s(%s)���˺�!  \n ����ʱ��Ϊ%d��%dСʱ. \n",
                ctime(time()), me->query("name"), me->query("id"),
                ob->query("name"), ob->query("id"),day,hour));
          ob->set("last_freeze_account", time());
          ob->save();
    } else
        write("�ʺŶ���ʧ�ܣ�\n");
    return 1;
}

int help(object me)
{
    write("
"HIY"ָ���ʽ:"NOR" "HIM"freeze "HIR"<"HIW""BLINK"id"NOR""HIR"> <"HIW""BLINK"n"NOR""HIR">"HIW" day "HIR"<"HIW""BLINK"n"NOR""HIR"> "HIW"hour"NOR"

���ָ�����������һ��ʱ���ڶ����Լ����ʺţ����ʺŶ����ڼ�
�κ��˶��޷�ʹ������ʺŵ�¼������㲻ϣ�����Լ������ڼ䱻
���˵����ʺţ�������ΪĳЩԭ������ѧϰ�������ŵȣ���һ��
ʱ���ڲ����¼����ð��Լ����ʺŶ���������
ע�⣺�����ʱ�������ʵ�е�ʱ�䣬�����Ǹ�����Ҳ��Ҫ̫����

"HIY"���磺"HIW"freeze ammy 0 day 5 hour"NOR" \n 
");
    return 1;
}
