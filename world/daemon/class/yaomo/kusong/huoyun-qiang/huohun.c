//���
//requirement:huomoforce,huoyun-qiang all over 60

#include <ansi.h>
 
inherit F_DBASE;
inherit SSERVER;
 
void remove_effect(object me, object target, int amount);
 
int perform(object me, object target)
{
        int skill_spear, skill_force, str_amount,spear_amount, delay;
        object weapon;
        if(me->query("family/family_name")!="���ƶ�")
		return notify_fail("����꡹ֻ�л��ƶ����˲ſ����ã�\n");
	if( !me->query("huohun_known") )
		return notify_fail("�㻹û��ѧ�ᡸ��꡹��\n");	
	if( time() - me->query_temp("huohun_end") < 10 )
		return notify_fail("����������㣬ʹ�á���꡹����Σ�ա�\n");	
        if (me->query_skill_mapped("force")!="huomoforce")
        	return notify_fail("����꡹������ϻ�ħ�ķ�����ʹ�á�\n");
        skill_force=me->query_skill("huomoforce",1);        
        if (skill_force<200) return notify_fail("��Ļ�ħ�ķ��������졣\n");
        skill_spear=me->query_skill("huoyun-qiang",1);
        if (skill_spear<200) 
           return notify_fail("���ǹ��̫��ˡ�\n"); 
        if( (int)me->query("force") < skill_force + 500 )      
                return notify_fail("�������������\n");
        if( (int)me->query("kee") < skill_spear + 500 )      
                return notify_fail("�����Ѫ������\n");
        if( (int)me->query_temp("shenli") )
                return notify_fail("���Ѿ����˹����ˡ�\n");
        weapon = me->query_temp("weapon");
        me->add("force", -skill_force);
        me->receive_wound("kee",skill_spear);
        message_vision(HIR"\n$Nҧ����⣬��"+weapon->name()+HIR"���һ��Ѫ��\n"NOR,me);
        message_vision(HIR"\n���ء���һ����"+weapon->name()+HIR"��ȼ�������һ𣬻��������һ������������\n"NOR, me);
 				
        spear_amount = skill_spear*(2+me->query("huohun_known"))/10;
        str_amount = skill_force*(2+me->query("huohun_known"))/10; 
        me->add_temp("apply/strength",str_amount);
        me->set_temp("apply/spear",spear_amount);
        me->set_temp("shenli", 1);
        delay = 15;
        if( me->query("lunhui_zhuanshi") > 4 )
        	delay = 30;
        me->start_call_out( (: call_other, __FILE__, "remove_effect", 
           me, str_amount,spear_amount:), delay);
         return 1;
}
 
void remove_effect(object me, int str_amount,int spear_amount)
{
        me->add_temp("apply/strength", -str_amount);
        me->delete_temp("apply/spear");
        me->delete_temp("shenli");
        me->set_temp("huohun_end",time());
        message_vision(HIR"$N�е�������֧�����һ���ľ�����ʧ�ˡ�\n"NOR,me);
}


