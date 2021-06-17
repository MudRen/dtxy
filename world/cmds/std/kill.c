#include <ansi.h>
#include "valid_kill.h";

//  inherit F_CLEAN_UP;
inherit SSERVER;
void do_kill(object,object);
int main(object me, string arg)
{
        object obj, guard_ob,target;
        string *killer, callname;
        int obj_level, me_level;
        string *vics;
        mapping killvic;

        if( !arg )
                return notify_fail("����ɱ˭��\n");

        if(!objectp(obj = present(arg, environment(me))))
                return notify_fail("����û������ˡ�\n");

        if( !obj->is_character() || obj->is_corpse() )
                return notify_fail("�����һ�㣬�ǲ����ǻ��\n");
       if( environment(me)->query("short") == HIR"CS��Ϣ��"NOR )
             return notify_fail("�㻹���ȴ��Ű�\n");
        if( !wizardp(me) && environment(me)->query("no_fight") && !obj->query("tongji/fanren") )
                return notify_fail("���ﲻ׼ս����\n");
        //the followed is added by vikee
 if ( !("/cmds/usr/pkgame"->query_pk()) )
   {
            if(userp(obj) && obj->query("age")<16 && !wizardp(me))

                return notify_fail("��վ��ʱ�������֡�\n");
 }
if ( (userp(me)) && (userp(obj)) )
{
if ( ((!me->query_temp("pkgame"))&&(obj->query_temp("pkgame"))) || ((me->query_temp("pkgame"))&&(!obj->query_temp("pkgame"))) )
 return notify_fail("������Ա�ͷǲ������֮�䲻��pk.\n");
}

        if(me->query("combat_exp")<50000 && userp(obj))
                return notify_fail("�Լ�����û���þ���ɱ�ˣ�\n");

        if(me->query("daoxing")<50000 && userp(obj))
                return notify_fail("�Լ�����û���þ���ɱ�ˣ�\n");       

        if(obj==me)
                return notify_fail("�� suicide ָ���ȽϿ�:P��\n");

    if(wizardp(obj)&&!wizardp(me)) 
       return notify_fail("ɱ��ʦ�����ǿ�������ɣ�\n");
      if(!valid_kill(me,obj,0)) return 0;
         callname = RANK_D->query_rude(obj);
   /**********************************/
    killvic=obj->query_temp("kill/target");
    if(mapp(killvic)&&sizeof(killvic))
       vics = keys(killvic); 
    /*****************************************/
        
        message_vision("\n$N����$n�ȵ�����" 
                + callname + "�����ղ������������һ��\n\n", me, obj);        


        if(!me->is_fighting()&&userp(obj))
       if((vics&& member_array(me->query("id"),vics)==-1)||!vics )
                me->set_temp("kill/target/"+obj->query("id"),1); 
              if(me->is_fighting()&&userp(obj))
                {
                    target=offensive_target(me);
                     if(target!=obj)
                if((vics && member_array(me->query("id"),vics)==-1)||!vics)
                   me->set_temp("kill/target/"+obj->query("id"),1); 
               }
        if( obj->query_temp("protected")
          && objectp(guard_ob=present(obj->query_temp("protect_ob"), environment(obj)))
          && (string)guard_ob->query_temp("protect")==obj->query("id")
          && guard_ob!=me ) {

        message_vision(HIC"$N����$n����˵�������ڴˣ����õ��ģ�\n"NOR,guard_ob,obj);
                        message_vision(HIC"$N����ǰȥ��ס��$n�Ĺ�����\n"NOR, guard_ob, me);
                        guard_ob->kill_ob(me);
                        me->kill_ob(guard_ob);
                }

        do_kill(me, obj);

        return 1;
}
void do_kill(object me, object obj)
{

        me->kill_ob(obj);
        if( !userp(obj) ){
        
                if(!obj->accept_kill(me) )
                obj->kill_ob(me);
				if((me->query("fangcun/panlong_longgong")=="begin")&&(me->query_temp("fangcun/panlong_longgong_longzhu")!="done")&&(obj->query("title")=="��������֮"))
                    obj->set_temp("longzhu_kill",me->query("id"));
                if((me->query("fangcun/panlong_hell_18")=="done")&&(me->query("fangcun/panlong_hell_longjin")=="begin")&&(obj->query("class")=="dragon"))
                    obj->set_temp("longjin_kill",me->query("id"));

        } else {
                obj->kill_ob(me);
                tell_object(obj, HIR "�����Ҫ��" + me->name() 
                        + "�����ಫ������Ҳ���������һ�� kill ָ�\n" NOR);

        }

}

int help(object me)
{
  write(@HELP
ָ���ʽ : kill <����>
 
���ָ������������ʼ����һ��������ҡ���ɱ���Է���kill �� fight ����
��ͬ����˫�������浶ʵǹ�ش򶷣�Ҳ����˵����������ˡ����� kill ֻ�赥��
��һ����Ը�Ϳ��Գ������������κ���ʹ�� kill ָ��Ὺʼս����ͨ�����
�Է��� NPC �Ļ�������Ҳ��ͬ������ʹ�� kill��

�����˶���ʹ�� kill ָ��ʱ����ֺ�ɫ�����������㣬����һ����Ҷ��ԣ����
��û�ж�һ������ʹ�ù� kill ָ��Ͳ��Ὣ�Է���Ĵ��˻�ɱ��( ʹ�÷�����
��)��

�������ָ��: fight

HELP
    );
    return 1;
}
