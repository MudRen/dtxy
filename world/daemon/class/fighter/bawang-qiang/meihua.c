//bawang-qiang, perform meihua
// /daemon/class/fighter/bawang-qiang/meihua
//÷������ Ҫ�����ǹ��70����110���Ժ��6��
//writted by jie 2001-2-10
#include <ansi.h>
#include <combat.h>
inherit SSERVER;

int perform(object me, object target)
{
        object weapon;
        int myskill,times, damage;
        string number,str;
        int cd = 6;
        myskill = (int)me->query_skill("bawang-qiang", 1);  
        weapon = me->query_temp("weapon");
      
        if( !target ) target = offensive_target(me);
        
       
        if( !target
        ||      !target->is_character()
        ||      target->is_corpse()
        ||      target==me)
                return notify_fail("��Ҫ��˭ʩչ��һ�С�÷����������\n");

        if(!me->is_fighting(target))
                return notify_fail("��÷��������ֻ����ս����ʹ�ã�\n");
                
        if(!wizardp(me) && me->query("family/family_name") != "������" )
                return notify_fail("�����Ķ�͵ѧ�����书��Ҳ���á�÷��������?\n");
        
        if( me->query("lunhui_zhuanshi") > 3 )
		cd = 5;
	if( time()-(int)me->query_temp("meihua_end") < cd )
                   return notify_fail("����������������\n");
//	if( me->query("pfm_meihua_on") != 1 )
//		return notify_fail("�㻹���ᡸ÷����������\n");                
                
        //if (me->query_temp("bawang"))
        //   return notify_fail("������ʩ�ð��־���û����������÷����������\n");
        
        if(!objectp(weapon = me->query_temp("weapon"))
           ||(string)weapon->query("skill_type")!="spear")
                return notify_fail("��÷��������Ҫ��ǹ���ܷ���������\n");

        if((int)me->query("max_force") < 1000 )
                return notify_fail("�������������\n");

	if((int)me->query("force") < 1200 )
		return notify_fail("����������㣡\n");

        if((int)me->query("sen") < (int)(me->query("max_sen")/2) )
                return notify_fail("��ľ����㣬û����ʩչ÷��������\n");

        if(myskill < 100)
                return notify_fail("��İ���ǹ�����𻹲�����\n");
        else 
            if(myskill <120){
                times = 3;        
                number = "��";}
            else
                if (myskill <160){
                    times = 4;
                    number = "��";}
                else
                    if(myskill <200 ){
                           times = 5;
                           number = "��";}
                     else{ 
                           times = 6;
                           number = "��";}
	me->set_temp("meihua_end",time());
        me->delete("env/brief_message");
	target->delete("env/brief_message");
	damage = me->query_str() + me->query_skill("spear");
	damage = damage + random(damage/3);
        target->add_temp("apply/parry",-damage/2);  
          target->add_temp("apply/dodge",-damage/2);
	message_vision(HIC"\n$Nһ����Х��"+ weapon->query("name")+ HIC"��һת�������������$n������"+number+"ǹ��ǹǹҪ����\n"NOR,me,target);
	me->add("force", -(times*40+60));
        for(int i=1;i<=times;i++)
        COMBAT_D->do_attack(me, target, weapon);
        //COMBAT_D->report_status(target, 0);
        me->receive_damage("sen", times*20);
	target->add_temp("apply/parry",damage/2);  
          target->add_temp("apply/dodge",damage/2);
	if( me->is_fighting(target) && environment(me) == environment(target) && times>5 ) //target->is_fighting()
	{
                target->receive_damage("kee",damage,me);
                target->receive_wound("kee", random(damage)/3, me);
                  			
		message_vision(HIR"\n$nֻ������ǰһ�����ؿ��ѱ�$N��"+ weapon->query("name")+ HIR"����һ����õ�����÷��������\n\n����������Ѫ��ӿ��������$n�Ѿ���Ϣ���٣���\n" NOR,me,target);
		COMBAT_D->report_status(target, 0);
		str=me->name()+"ʹ����������ѧ��"HIR"÷������"HIM"����"+target->name()+NOR+HIM"����һ��Ѫɫ���õ�÷�����˻�Ȫ��";
		if( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
    { 
        	message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
    }
	}
        me->start_busy(1+random(2));
        return 1;
}

