//xiangxi.c  
//created by DHXY-EVIL 2000.7.7
//Modified by vikee for xlqy-zq station 2000-12-5 9:05 .The CopyRight was keeped by DHXY-evil.

#include <ansi.h>
#include <combat.h>
#include <condition.h>
inherit SSERVER;

int perform(object me, object target)
{       
        string msg="";
        int damage,wound;
        object weapon=me->query_temp("weapon");
        int cd = 6;
        if( !target ) target = offensive_target(me);
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ����˼��������\n");

        if(!me->is_fighting(target))
                return notify_fail("����˼������ֻ����ս����ʹ�ã�\n");
        
        if(me->query("family/family_name")!="��ɽ��")
                return notify_fail("����ɽ�����á���˼��������\n");
        
        if((int)me->query("faith") < 500 )
                return notify_fail("��������ҳ϶Ȳ�����\n");
//if(me->query("shushan/ask_zuidao_go") !=1 )
//return notify_fail("û�����ĵ���ᣬ�ò��˲���ġ���˼��������\n");
        
        if (me->query_skill_mapped("force")!="zixia-shengong")
        	return notify_fail("����˼��������������ϼ�������ӣ�\n");
        	
        if((int)me->query("max_force") < 500 )
                return notify_fail("�������������\n");

        if((int)me->query("force") < 300 )
                return notify_fail("����������㣡\n");
        if((int)me->query("sen") < 300 )
                return notify_fail("��ľ����㣬û����ʩ���⹦��\n");
if((int)me->query_skill("zixia-shengong", 1) < 100)
                return notify_fail("�����ϼ����Ϊ��������ʹ����һ�л������ѣ�\n");
 if((int)me->query_skill("canxin-jian", 1) < 100)
                return notify_fail("��Ĳ��Ľ���Ϊ��������ʹ����һ�л������ѣ�\n");
        if( me->query("lunhui_zhuanshi") > 1 )
		cd = 5;
        if( time()-(int)me->query_temp("xiangsi_end") < cd )
                return notify_fail("�����ö��ˣ��Ͳ����ˣ�\n");
        me->set_temp("xiangsi_end",time());
        message_vision(MAG"$N��˼�����͵�ʩ�����Ľ��ľ��С���˼����������$n��������������\n"NOR,me,target);
        me->set("xiangsi", 8);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	switch (random(4))
        {
         case 0:
              {
               message_vision(HIG"$n�������е���˼֮���Ⱦ�������鶾��\n"NOR,me,target);
               target->apply_condition("xiangsi",20);
               break;
               }
         case 1:
              {
               message_vision(HIG"һ�ɾ�������$n��$n�ƺ����˵���⣡\n"NOR,me,target);
               target->apply_condition("drunk",20);
               break;
              } 
         case 2:
              {
               message_vision(HIG"��������Ϊ���\n"NOR,me,target);
               message_vision(HIG"���޺ۣ�����ţ��������³������\n"NOR,me,target);  
               target->apply_condition("xiang_air",20);
               break;
              }
         case 3:
              {
               break;
              }
        }
	me->set("xiangsi", 9);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	switch (random(4))
        {
         case 0:
              {
               message_vision(HIG"$n�������е���˼֮���Ⱦ�������鶾��\n"NOR,me,target);
               target->apply_condition("xiangsi",20);
               break;
              }
         case 1:
              {
               message_vision(HIG"һ�ɾ�������$n��$n�ƺ����˵���⣡\n"NOR,me,target);
               target->apply_condition("drunk",20);
               break;
              }
         case 2:
              {
               message_vision(HIG"��������Ϊ���\n"NOR,me,target);
               message_vision(HIG"���޺ۣ�����ţ��������³������\n"NOR,me,target);
               target->apply_condition("xiang_air",20);
               break;
              }
         case 3:
              {
         break;
              }
        }
	me->set("xiangsi", 10);
	COMBAT_D->do_attack(me, target, me->query_temp("weapon"));
	switch (random(4))
        {
         case 0:
              {
               message_vision(HIG"$n�������е���˼֮���Ⱦ�������鶾��\n"NOR,me,target);
               target->apply_condition("xiangsi",20);
               break;
              }
         case 1:
              {
               message_vision(HIG"һ�ɾ�������$n��$n�ƺ����˵���⣡\n"NOR,me,target);
               target->apply_condition("drunk",20);
               break;
              }
         case 2:
              {
               message_vision(HIG"��������Ϊ���\n"NOR,me,target);
               message_vision(HIG"���޺ۣ�����ţ��������³������\n"NOR,me,target);  
               target->apply_condition("xiang_air",20);
               break;
              }
         case 3:
              {
               break;
               }
        }
	me->delete("xiangsi");
        me->start_busy(1+random(2));
        message_vision(HIG"$N�ġ���˼�������ù���ϣ����ص���,�����չ�.\n"NOR,me,target);
        message_vision(msg,me,target);
        me->add("kee", -50);
        me->add("force", -100);
        me->add("sen",-50);
        return 1;
}
