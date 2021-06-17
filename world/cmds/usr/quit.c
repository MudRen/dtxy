
// quit.c

#include <command.h>
#include <ansi.h>

inherit F_DBASE;
inherit F_CLEAN_UP;

int do_drop(object me, object obj);
void do_yorn(string yn, object me, string arg);
void create()
{
        seteuid(getuid());
        set("name", "����ָ��");
        set("id", "quit");
}

// if force_quit==1, then don't check whether allow quit.
// used by quit after disconnected or idled too long.
// mon 7/5/98
int main(object me, string arg, int force_quit)
{
        int i;
        object *inv, link_ob;
object ob;

        link_ob = me->query_temp("link_ob");

        if(!force_quit) {
        if ( me->query_temp("no_move") )
                return notify_fail("�㱻��ס�ˣ������˵ó���Ϸ��\n");
        if ( me->query_condition("no_pk_time") > 120 )
                return notify_fail("���ɱ���ˣ������˳���Ϸ��\n");
        if ( me->query_temp("pkgame") )
                return notify_fail("�������������Ҳ����ѽ��\n");
        if(!me->query_temp("suicide_countdown")) {
          if( me->is_busy() )
                return notify_fail("( ����һ��������û����ɣ������˳���)\n");
        } //to allow halt suicide :D by mon 9/9/97

        if( !wizardp(me) && environment(me) &&
          environment(me)->query("no_quit") && link_ob )
                        return notify_fail("���ﲻ׼�˳���Ϸ��\n");
        }
        if (!wizardp(me) && time()-(int)me->query("birthday") < 120 )
         {
          write("\n���������˺����½��ģ�Ϊ�˼���ϵͳ����������\n");
          write("��Ϸ�涨��������2�������ϲſɴ浵��\n\n");
          write("��������Ҫ��������˺���"HIY"[Y/N]"NOR);
          input_to("do_yorn",me,arg);
         }
       else
        {
        if( !wizardp(me) && (!link_ob || (
            link_ob && !link_ob->is_character()) ) ) {
                inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                        if( !inv[i]->query_autoload() )
                                do_drop(me, inv[i]);
        }

        // We might be called on a link_dead player, so check this.
        if( link_ob ) {

                // Are we possessing in others body ?
                if( link_ob->is_character() ) {
                        write("��Ļ��ǻص�" + link_ob->name(1) + "�����ϡ�\n");
                        exec(link_ob, me);
                        link_ob->setup();
                        return 1;
                }

                link_ob->set("last_off", time());
                link_ob->set("last_leave", query_ip_name(me));
                link_ob->save();
                destruct(link_ob);
        }
         write("\n��ӭ�´�������\n");
         if(!wizardp(me) || !me->query("env/invisibility"))
         message("system", me->name() + "�뿪��Ϸ��\n", environment(me), me);
         if (!wizardp(me))
         CHANNEL_D->do_channel(this_object(), "sys",
                me->name() + "(" + capitalize(me->query("id")) + ")" + "�뿪��Ϸ�ˡ�");
         else
         CHANNEL_D->do_channel(this_object(), "wiz",
                me->name() + "(" + capitalize(me->query("id")) + ")" + "�뿪��Ϸ�ˡ�");
         me->save();
     if (!wizardp(me))
{
      ob = find_object("/d/topten/topten");
//     ob->sort_board(me);

  }
         destruct(me);
        }
        return 1;
}
void do_yorn(string yn, object me, string arg)
{
     int i;
     string myid, couple;
     object *inv;
     if(!me) return;
     if(!yn) {
         write("ʲô��\n");
         return;
     }
     if(yn[0]=='y' || yn[0]=='Y' )
     {
        write("\n\n�����������˺ţ������ؼ�����Ϸ��\n");
        return;
     }
                write("\n");
                inv = all_inventory(me);
                for(i=0; i<sizeof(inv); i++)
                        if( !inv[i]->query_autoload() )
                                do_drop(me, inv[i]);
        seteuid(getuid());
        rm( me->query_save_file() + __SAVE_EXTENSION__ );
        myid=me->query("id");
        rm( "/data/login/"+myid[0..0]+"/"+myid+ __SAVE_EXTENSION__ );
        rm( "/data/playerhomes/h_"+myid+ __SAVE_EXTENSION__ );
        rm( "/data/mail/"+myid[0..0]+"/"+myid+ __SAVE_EXTENSION__ );
        couple=me->query("coupld/id");
        if(couple)
          rm("/data/mail/"+couple[0..0]+"/"+couple+__SAVE_EXTENSION__);
      LOGIN_D->set_banned_name(me->name(1),0);
      write("\n"+me->name()+"����ӭ���´�������\n");
      message("system", me->name() + "("+me->query("id")+")��Զ���뿪�����ǣ�\n", environment(me), me);
      CHANNEL_D->do_channel(this_object(), "sys",
       me->name() + "(" + capitalize(me->query("id")) + ")" + "�����������˺š�");
      log_file("no_reg",
      sprintf("%s(%s) abandoned on %s from %s\n", geteuid(me), me->name(), ctime(time()), (string)query_ip_name(me) ) );
      destruct(me);
      return;
}

int do_drop(object me, object obj)
{
        //if obj is a self-made fabao, save first...
        //if( obj->query("series_no") && obj->query("fabao") ) obj->save();

        if( obj->query("no_drop") ){
                destruct(obj);
                return 0;
        }
        if (obj->move(environment(me))) {
                if( obj->is_character() )
                        message_vision("$N��$n�ӱ��Ϸ������������ڵ��ϡ�\n", me, obj);
                else {
                        message_vision( sprintf("$N����һ%s$n��\n",     obj->query("unit")), me, obj );
                        if( !obj->query("value") && !obj->value() ) {
                                tell_object(me,"��Ϊ������������ֵǮ���������ǲ�����ע�⵽���Ĵ��ڡ�\n");
                                destruct(obj);
                        }
                }
                return 1;
        }
        return 0;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : quit

��������ʱ�뿪ʱ, �����ô�һָ�
HELP
    );
    return 1;
}
