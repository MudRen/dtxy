//modified by vikee 
//2000.10

#include <ansi.h>
#include "valid_kill.h";

inherit F_CLEAN_UP;
void do_tianlong(object,object);
int main(object me, string arg)
{
        object obj, guard_ob;
        string *killer, callname;

         if(me->query_temp("12gong/tianlong")!="done")
               return notify_fail("û��ͯ���Ĵ���,����λ�������?\n");

		 if( !wizardp(me) && environment(me)->query("no_fight") )
                return notify_fail("���ﲻ׼ս����\n");

if( environment(me)->query("name")=="�ٻ���" )
 return notify_fail("����֮Σ,��̫��!\n");
        if( !arg )
                return notify_fail("�����˭��������\n");

        if(!objectp(obj = present(arg, environment(me))))
                return notify_fail("����û������ˡ�\n");
if (userp(obj))
                        return notify_fail("���������¶���?\n");

        if( !obj->is_character() || obj->is_corpse() )
                return notify_fail("�����һ�㣬�ǲ����ǻ��\n");

        if(obj==me)
                return notify_fail("�� suicide -fָ���ȽϿ�:P��\n");
    
             if(obj->query("age")<=16 && userp(obj))
                return notify_fail("�������Ը�С���ӣ���̫û������!\n");
        // forbid to kill a player whose mudage <17 .here is added by vikee :P
        
   
        

    //    if(!valid_tianlong(me,obj,0)) return 0;

        callname = RANK_D->query_rude(obj);

        message_vision("\n$N����$n�ȵ�����" 
                + callname + "�����ҵľ���[����]����\n\n", me, obj);        

       if (arg=="shura")
       {
		message_vision(HIY"\n\n\nֻ��$N�����ֳ�һ�����������צ����ץס$n,�������!\n\n"NOR, me, obj); 
         message("chat",HIY+"ͻȻ��ɽ�򹬱�������ǿ���С����,ֱ�����,����һ�����ǻ�����ʧ�����!\n"NOR,users());
		 obj->unconcious();
		 me->kill_ob(obj);
		 return 1;
	   }
        do_tianlong(me, obj);

        return 1;
}

void do_tianlong(object me, object obj)
{
        me->kill_ob(obj);
        if( !userp(obj) ){
                if(!obj->accept_kill(me) )
                obj->kill_ob(me);
        } else {
                obj->fight_ob(me);
                  tell_object(obj, HIR""+me->name()+"����ʹ���˾���[����]\n"NOR);
              }
message_vision(HIY"\n\n\nֻ��$N�����ֳ�һ�����������צ����ץס$n,ֻ�����!\n\n"NOR, me, obj);
tell_object(obj,HIR"\n\n\n��ǰ������,�����������۾�,���ߴ���������ŭ��.�㲻֪��"+
"���˶��,ͻȻץס��ľ���צ��һ��,�㳯����ֱ׹����ȥ.........."NOR);
  if (obj->is_manmade_npc()) {
      obj->set("combat_exp", obj->query("combat_exp")/7);
      obj->set("daoxing", obj->query("daoxing")/7);
  }

obj->unconcious();
me->delete_temp("12gong/tianlong");
}


/*int help(object me)
{
  write(@HELP
ָ���ʽ : tianlong <����>
 
��������,�ǻƽ�ʥ��ʿԪ��,�����ͯ���ľ���,��ͨ���ƽ�ʮ����ʱ�����������'������ɽ��'
    );
  return 1;
}
*/
