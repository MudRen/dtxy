// edit by canoe
#include <ansi.h>

inherit F_CLEAN_UP;
int help(object me);

int main(object me, string arg)
{
        object ob;
        string str,reason,name;
        if( !arg) return help(me);      

         if( sscanf(arg, "-o %s", arg) ) 
           {
                        ob = find_player(arg);
                        if(!ob) ob = find_living(arg);
                        if(!ob) ob = LOGIN_D->find_body(arg);
                        if(!ob || !me->visible(ob)) return notify_fail("û������ˡ�\n");
                        if(ob->query("punished")!=0) {
              log_file("PUNISH_PLAYER", sprintf("%s(%s) free %s from punish on %s.\n", 
                me->name(1), geteuid(me), arg, ctime(time()) ) );
              write("�����ͷ� " + ob->name()+"("+arg+ ")��\n");
              tell_object(ob,"���������ͷ��ˣ�\n");
               CHANNEL_D->do_channel(this_object(), "rumor", HIW+ob->name()+HIM"�������ͷ��ˣ�");
              ob->delete("punished");
              ob->move("/d/city/kezhan");
              ob->set("startroom","/d/city/kezhan");
              ob->save();
            }
else return notify_fail ("������û�й������Ρ�\n");
        }
           else if ( sscanf(arg, "%s because %s",name, reason)==2 ) 
        {
          ob = find_player(name);

         if(!ob) ob = find_living(name);
        
        if(!ob) ob = LOGIN_D->find_body(name);

        if(!ob || !me->visible(ob)) return notify_fail("û������ˡ�\n");

        if( wizhood(me) != "(admin)"
        &&      wiz_level(me) <= wiz_level(ob) ||name=="canoe")
                return notify_fail("��û�гͷ�" + ob->name() + "��Ȩ����\n");

        if( me==ob )  return help(me);
        if (ob->query("punished")) return notify_fail("������Ѿ������������ˡ�\n");
          message_vision(HIB"��Ȼ�����������ذ���\n$N��һ�����������ˣ�\n"NOR,ob);
                tell_object(ob,"������"+reason+"�����������Σ�\n");
                ob->set("punished",1);
                  ob->move("/d/wiz/punish1");
    if( userp(ob) ) log_file("PUNISH_PLAYER",
 sprintf("%s(%s) punish %s on %s because %s.\n", me->name(1),
        geteuid(me), ob->name(1),ctime(time()),reason ) );
        if( wizardp(ob)) 
      tell_object(ob, HIW + me->name(1) + "����������Ρ�\n" + NOR);
CHANNEL_D->do_channel(this_object(), "rumor", ob->name()+"��Ϊ"HIW+reason+HIM+"�����񼫣�������"HIW"����"HIM"��");
      }
else  return help(me);
  return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ��
  silao <id> because <ԭ��>   ����Ҵ�������
  silao -o <id>  ������ͷ�
HELP
        );
        return 1;
}
