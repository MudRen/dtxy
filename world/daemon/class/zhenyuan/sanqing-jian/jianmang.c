
//jianmang.c
//write by yesi

#include <ansi.h>

 
void remove_effect(object me);
void check(object me);

int perform(object me, object target)
{
        int skill_sanqing, skill_sword, skill_force,skill_spells,attack_amount;
        object weapon=me->query_temp("weapon");
        
        skill_force=me->query_skill("zhenyuan-force",1);
        if( skill_force > 300 ) skill_force=300;
	
	skill_spells=me->query_skill("taiyi",1);
	if( skill_spells > 300 ) skill_spells=300;
	skill_sanqing = me->query_skill("sanqing-jian"); 
	attack_amount=(skill_spells+skill_force)/10;
        attack_amount = attack_amount * 2 + random(attack_amount);
        if( me->query_temp("jianmang") )  //{remove_effect(me); return 1;}
        	return notify_fail("������ʹ�ý�â��\n");
        //if( time()-(int)me->query_temp("jianmang_end") < 10 )
         //          return notify_fail("����������������\n");
        if(!wizardp(me) && me->query("family/family_name") != "��ׯ��")
                return notify_fail("[��â]����ׯ�۲���֮�ܣ�\n");           
        if (skill_force < 100) return notify_fail("�����Ԫ����Ϊ�������������˽�â��\n");

        if (skill_spells < 100) return notify_fail("���̫���ɷ���Ϊ�������������˽�â��\n");
        
        if (me->query_skill_mapped("force")!="zhenyuan-force")
            return notify_fail("����â�����������Ԫ�񹦲���ʹ�á�\n");
              
        if (me->query_skill_mapped("spells")!="taiyi")
            return notify_fail("����â���������̫���ɷ�����ʹ�á�\n");
        
        if((int)me->query_skill("sanqing-jian", 1) < 160)
                return notify_fail("������彣�����𻹲������������ɽ�â��\n");

                      
            if( (int)me->query("force") < 300 )      
            return notify_fail("�������������\n");
        
		        
        me->add("force", -skill_force);
       
        message_vision(HIY"$N�߶�������ͬʱ����ԣ�����Ԫ�񹦺�̫�ҷ�������ע��"+weapon->name()+HIY"������������罣â��˸˸���ԡ�\n" NOR, me);
        me->add_temp("apply/damage",attack_amount);  
        me->set_temp("jianmang_damage",attack_amount);
	me->set_temp("jianmang", 1);
	me->start_call_out( (: call_other, __FILE__, "remove_effect", me :), attack_amount / 2);
        //me->set_temp("jianmang_time",skill_force);
        //call_out("check", 1, me);
         
         return 1;
}
 
/*
void check(object me)
{      
	object weapon;
if(!me) return;
	             
if(!me->query_skill_mapped("force")) remove_effect(me);
	if(me->query_skill_mapped("sword") != "sanqing-jian"
	|| me->query_skill_mapped("force") != "zhenyuan-force" 
	|| me->query_skill_mapped("spells") != "taiyi" 
	|| !objectp(weapon=me->query_temp("weapon")) 
	|| (weapon->query("apply/skill_type") != "sword" 
	&&  weapon->query("skill_type") != "sword" )) 
		remove_effect(me);			
	else if(me->query_temp("jianmang_time")<1)
	remove_effect(me);			
	else {  me->add_temp("jianmang_time",-1);
		call_out("check", 1, me);
	     }
}
*/



void remove_effect(object me)
{       
        if(!me) return;
        me->add_temp("apply/damage", -me->query_temp("jianmang_damage"));
        //remove_call_out("check");
        me->delete_temp("jianmang");
        me->delete_temp("jianmang_damage");
        message_vision(HIB"$N�Ľ�â������ȥ��\n" NOR, me);
        //me->set_temp("jianmang_end",time());
}


