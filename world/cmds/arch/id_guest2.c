// boy redrose 2000/05  
// id_guest2.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;

        if( !arg ){
                    write("ָ���ʽ��id_guest2 <ĳ��>\n��Υ�������ʹ���ߴ���ӭ������\n");
                            return 1;
                }

         if( sscanf(arg, "-d %s", arg) ) 
           {
                        ob = find_player(arg);
                        if(!ob) ob = find_living(arg);
                        if(!ob) ob = LOGIN_D->find_body(arg);
                        if(!ob || !me->visible(ob)) return notify_fail("û������ˡ�\n");
                        if(ob->query("punished")!=0) {
              log_file("PUNISH_PLAYER", sprintf("%s(%s) free %s from punish on %s.\n", 
                me->name(1), geteuid(me), arg, ctime(time()) ) );
                tell_object(me,HIW+ob->name()+""HIR"�����ͷ���"NOR"\n");
              ob->delete("punished");
              ob->move("/d/city/kezhan");
                     return 1;
                   ob->set("startroom","/d/city/kezhan");
                                ob->save();
                               }
                write("���ʹ����û�б�����ӭ������\n");
                return 1;
            }

        ob = find_player(arg);

        if(!ob) ob = find_living(arg);
        
        if(!ob) ob = LOGIN_D->find_body(arg);

        if(!ob || !me->visible(ob)) return notify_fail("û������ˡ�\n");

        if( wizhood(me) != "(wizard)"
        &&      wiz_level(me) <= wiz_level(ob) )
                return notify_fail("��û�гͷ�" + ob->name() + "��Ȩ����\n");

        if( me==ob ) return notify_fail("�ͷ���������id_guest2 -d <ID> ����ͷ���\n");
                     
                tell_object(me,HIW+ob->name()+""HIR"���������ӭ������"NOR"\n");
                ob->set("punished",1);
                 ob->move("/d/wiz/guest");
                if( userp(ob) ) log_file("PUNISH_PLAYER",
                              sprintf("%s(%s) punish %s on %s.\n", me->name(1), geteuid(me), ob->name(1),
                                           ctime(time()) ) );
        return 1;
}
int help()
{
        write(@TEXT
ָ���ʽ��id_guest2 <ĳ��>

��Υ�������ʹ���ߴ���ӭ������id_guest2 -d <ĳ��>��ȡ���ͷ���
TEXT
        );
        return 1;
}

//���ļ�id_guest1 ������ ���ļ�id_guest2 hoho
