#include <ansi.h>
inherit SSERVER;
int perform(object me, object target)
{
        object weapon,ob;
        int j,skill,num;
        string msg,str;
	int cd = 10;
        //if (me->query("fangcun/panlong_accept")!="done")
        //   return 0;
	if( me->query("fangcun/panlong_qiansi_finish")!=1 || me->query("fangcun/panlong_noway") )
		return 0;
                 if((me->query("family/family_name") != "����ɽ���Ƕ�" ) && !wizardp(me))
                return notify_fail("�����Ķ�͵ѧ�����书��Ҳ���á�������ʽ��?\n");

		if( !target ) target = offensive_target(me);

        if( !target

        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��������ʽ��ֻ����ս����ʹ�á�\n");

        if (!objectp(weapon = me->query_temp("weapon"))
                || (string)weapon->query("skill_type") != "stick")
                return notify_fail("��������ʽ�������ù�������ʩչ��\n");

             if( (int)me->query_skill("qianjun-bang", 1) < 150 )
                return notify_fail("��ġ�ǧ������������죬����ʹ�á������˴򡹡�\n");

        if( (int)me->query("force") < 1200  )
                return notify_fail("�������������\n");
        if( me->query("lunhui_zhuanshi") > 1 )
		cd -= me->query("lunhui_zhuanshi") - 1;
        if(time()-me->query_temp("pl_end")<cd) return notify_fail("���ʹ��������ͻ������������\n");
   if (me->query("fangcun/panlong_accept")=="done" && target->query_temp("jldl"))
         {
                target->delete_temp("jldl");
                target->set_temp("jldl_end", time() );
 		message_vision(HIR"$N����������ʽ�����ǿ���������$n�Ľ�������Ҳʧȥ�����ã�\n\n\n"NOR,me,target);
         }
         skill=me->query_skill("qianjun-bang",1);
         num = skill/50;
         skill = skill/2;
         if (me->query("fangcun/panlong_accept")=="done")
         {
         	target->start_busy(1);
         	skill = skill*2;
         }
         target->add_temp("apply/dodge",-skill/2);
         target->add_temp("apply/parry",-skill/2);
	 msg = HIG "$N�������У����е�$n"+HIG"����"+HIY"�������׺�"+HIG"��ʱ����������Ӱ�ӡ�\n"NOR;
         message_vision(msg, me, weapon);
      	 me->add_temp("apply/attack",skill/2);
    	 me->add_temp("apply/damage",skill/2);
    	 if (me->query("fangcun/panlong_accept")=="done" || num > 8 ) num = 8;
    	 me->add("force", -(100+num*50));
       for(j=1;j<=num;j++)
   {
   msg = HIR "�����Ӱ�У�$N�ҳ���"+HIY+chinese_number(j)+HIR+"����\n"NOR;
   message_vision(msg, me, weapon);
   if( random(8) == 1 ) me->set_temp("QJB_perform",8);
   if( !me->query_temp("QJB_perform") && random(12) == 1 ) me->set_temp("QJB_perform",7);
   COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
   me->delete_temp("QJB_perform");
   }    
      //if(me->query("id")!="take")
	//{
		me->set_temp("pl_end",time());
        me->start_busy(2);
	//}
    me->add_temp("apply/attack",-skill/2);
    me->add_temp("apply/damage",-skill/2);
            target->add_temp("apply/parry",skill/2);
            target->add_temp("apply/dodge",skill/2);
	if( !random(5) && me->query("fangcun/panlong_accept")=="done" && (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) )  
 	{ 
 		str=me->name()+NOR+HIM"ʹ�������ѧ"+NOR+HIY"��������ʽ��"+HIM"����˵"+target->name()+NOR+HIM"����Ŀ����"+BLINK+HIC"�������׺���̤��Х����"+NOR+HIM"���澰���Ŀ��ȥ��";
                message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
        }
        return 1;
}
