//����Ц
//lestat for �ݹǵ� perform
#include <ansi.h>
#include <combat.h>
inherit SSERVER;
int perform(object me, object target)
{
      object weapon=me->query_temp("weapon");
      int enhance,damage;
      string msg,str;
      int xcd = 5;
      int djcd = 10;
      if (!weapon) return 0;
      if( !target ) target = offensive_target(me);
      if( !target || !target->is_character()||target->is_corpse()||target==me)
          return notify_fail("��Ҫ����˭��\n");
      if( !wizardp(me) && me->query("family/family_name")!="�ݿ�ɽ�޵׶�" )
          return notify_fail("������Ц��ֻ���޵׶����˲ſ����ã�\n");
      if ( !wizardp(me) 
      		&& (me->query_skill("moonforce",1)     
		|| me->query_skill("ningxie-force",1)
		|| me->query_skill("lengquan-force",1)
		|| me->query_skill("zixia-shengong",1)
		|| me->query_skill("zhenyuan-force",1)
		|| me->query_skill("tonsillit",1)
		|| me->query_skill("dragonforce",1)
		|| me->query_skill("huomoforce",1)
		|| me->query_skill("wuxiangforce",1)
		|| me->query_skill("lotusforce",1)
		|| me->query_skill("xuanzong-force",1)
		|| me->query_skill("butian-force",1)
		|| me->query_skill("jiuyin-xinjing",1)) )
          return notify_fail("�㲻��ɢ�˱����ڹ�������ѧ����Ц����\n");
      if( me->query("lunhui_zhuanshi") > 4 )
          xcd = 6;
      if( time()-(int)me->query_temp("xiao_end") < xcd )
          return notify_fail("�����ö�Ͳ����ˣ�\n");
      if (!target->is_fighting(me))
          return notify_fail("����û���ڴ�ܣ�\n");
      //if (target->is_busy())
      //    return notify_fail("�Է������æ�����ˣ��ŵ������ɣ�\n");
      if (me->query_skill("huntian-qigong",1)<100)
          return notify_fail("����ڹ�̫��������Խ���������\n");
      if (me->query_skill("kugu-blade",1)<100) 
          return notify_fail("�㻹���ȰѾ��������ڿݹǵ����ϰɡ�\n");
      if (me->query_skill("yinfeng-zhua",1)<100) 
          return notify_fail("�������צ̫�ǿ���񹦲���Ц�����ˡ�\n");
      if (me->query_skill("qixiu-jian",1)<100)
         return notify_fail("������޽�����ô�ã�������˼���ڵ��������ۣ�\n");
      if (me->query_skill_mapped("force")!="huntian-qigong")
            return notify_fail("����Ц������ϻ�����������ʹ�á�\n");
      if (me->query_skill_mapped("unarmed")!="yinfeng-zhua")
            return notify_fail("����Ц�����������צ���ܷ���������\n");
      if (me->query_skill_mapped("sword")!="qixiu-jian")
            return notify_fail("����Ц����������޽����ܷ���������\n");
      if (me->query("force")<800)
           return notify_fail("���������̣����Գ��С�\n");

    me->add("force", -100);
    seteuid(getuid());
////����
    me->set("actions", (: call_other, SKILL_D("qixiu-jian"), "query_action" :) );   
    message_vision(HIB"$NĬ�˻���������ͻȻ��ʹ�����޽���������"+weapon->name()+HIB"ֱȡ$n��\n"NOR,me,target);
    weapon->set_temp("original/use_apply_skill",weapon->query("use_apply_skill"));
    weapon->set_temp("original/skill_type",weapon->query("apply/skill_type"));
    weapon->set("use_apply_skill",1);
    weapon->set("apply/skill_type","sword");
    enhance=me->query_skill("qixiu-jian",1);
    me->add_temp("apply/attack", enhance);  
    damage=me->query_skill("kugu-blade",1);
    damage=(damage+random(damage))/5;
    me->add_temp("apply/damage",damage);        
    COMBAT_D->do_attack(me, target, weapon);
    weapon->set("use_apply_skill",weapon->query_temp("original/use_apply_skill"));
    weapon->set("apply/skill_type",weapon->query_temp("original/skill_type"));
    me->add_temp("apply/attack",-enhance);
    me->add_temp("apply/damage",-damage);
    me->reset_action();
////����
    me->set("actions", (: call_other, SKILL_D("yinfeng-zhua"), "query_action" :) );   
    message_vision(HIC"\n$N������ʽ���ϣ�����һЦ�������յ���צ��һ������ֱ��$n��\n"NOR,me,target);
    //weapon->unequip();
    weapon->set_temp("original/use_apply_skill",weapon->query("use_apply_skill"));
    weapon->set_temp("original/skill_type",weapon->query("apply/skill_type"));
    weapon->set("use_apply_skill",1);
    weapon->set("apply/skill_type","unarmed");
    enhance=me->query_skill("yinfeng-zhua",1);
    me->add_temp("apply/attack", enhance);  
    damage=me->query_skill("huntian-qigong",1);
    damage=damage/2;
    me->add_temp("apply/damage",damage);        
    COMBAT_D->do_attack(me, target);
    weapon->set("use_apply_skill",weapon->query_temp("original/use_apply_skill"));
    weapon->set("apply/skill_type",weapon->query_temp("original/skill_type"));
    me->add_temp("apply/attack",-enhance);
    me->add_temp("apply/damage",-damage);
    //weapon->wield();
    if( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
                       {str=target->name()+HIM"��"+me->name()+"���ݿ�ɽ��ѧ"NOR+HIC"������Ц��"+HIM"�����ˣ���˵"+target->name()+"�������ϻ�����΢Ц��";
	                 message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
	               }
    me->reset_action();
    if( me->query("lunhui_zhuanshi") )
	djcd -= me->query("lunhui_zhuanshi");
    if( me->query("daojian_known") && time()-(int)me->query_temp("daojian_end") > djcd ) //10s ��һ�Σ����⹥��
    {
    	me->set_temp("daojian_end",time());
    	message_vision(RED"\n$N����ͻȻ�ӹ�һĨ���죬"+weapon->name()+RED"�Ϸ���ѪӰ���أ�\n" NOR, me);
    	call_out("blade_attack",1,me,target);
    }
    me->set_temp("xiao_end",time());
//    me->start_busy(random(2)+1);
    return 1;
}

void blade_attack(object me, object target)
{
	int enhance, damage;
	object weapon;
	string str;
	if( !me ) return ;
	if( !target ) target = offensive_target(me);
      	if( !target || !target->is_character()||target->is_corpse()||target==me ) return ;
      	if( !target->is_fighting(me) ) return ;
      	if( (int)me->query("force", 1) < 1000 )
        {
        	message_vision(HIB"$N�������㣬�������У�\n"NOR,me);
        	return ;
        }
      	weapon = me->query_temp("weapon");
      	enhance = me->query_skill("huntian-qigong",1);
    	damage = me->query_skill("kugu-blade",1);
    	damage = damage + me->query_str();
    	if( weapon )
    		message_vision(RED"\nͻȻ֮�䣬$N��"+weapon->name()+RED"бб����������һƬѪӰ�ȷ����$n��\n" NOR, me,target);
    	else
    		message_vision(RED"\nͻȻ֮�䣬$N���ı�ð��죬����һƬѪӰ�ȷ����$n��\n" NOR, me,target);
    	if( random(enhance) > random(target->query_skill("force",1) /4) &&
            random(me->query("combat_exp")) > random(target->query("combat_exp") /4) )
        {
        	me->add("force",-damage/3);
        	damage = damage + random(damage/2);
        	target->receive_damage("kee",damage,me);
        	target->receive_wound("kee",damage,me);
        	message_vision(HIR"\n��仯����ͻȻ��$n���ܲ�����������ʴ�ǵ�Ѫ������Χס��\n" NOR, me,target);
        	message_vision(HIR"$n�ҽ�һ������Ѫ���г�ͻ������$N����һ����$n���ѱ����Ŀȫ�ǣ�\n" NOR, me,target);
        	if( me->query("daojian_known") > 1 ) me->set_temp("hit",1);
        	COMBAT_D->report_status(target,1);
        	message_vision(RED"\nѪ�����$n�ľ�����Ѫɫ��ʢ��\n" NOR, me,target);
        	if( me->query("lunhui_zhuanshi") > 1 )
        		call_out("sword_attack",1,me,target);
        	else
        		call_out("sword_attack",2,me,target);
        }
        else
        {
        	me->add("force",-60);
        	message_vision(HIB"$n�������磬����ܹ���Ѫ��\n" NOR, me,target);
        	call_out("sword_attack",1,me,target);
        }
        message_vision(RED"\n����Ѫ���������ԣ�Ƭ�̺����$N������������$N���ڣ�\n" NOR, me);
        if (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0))  
        {
        	str=target->name()+HIM"��"+me->name()+"ץ�����飬���޶�����";
	        message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
	}
	return ;
}

void sword_attack(object me, object target)
{
	int enhance, damage;
	object weapon;
	string str;
	if( !me ) return ;
	if( !target ) target = offensive_target(me);
      	if( !target || !target->is_character()||target->is_corpse()||target==me ) return ;
      	if( !target->is_fighting(me) ) return ;
      	if( (int)me->query("force", 1) < 1000 )
        {
        	message_vision(HIB"$N�������㣬�������У�\n"NOR,me);
        	return ;
        }
      	weapon = me->query_temp("weapon");
      	enhance = me->query_skill("huntian-qigong",1);
    	damage = me->query_skill("qixiu-jian",1);
    	damage = damage + me->query_str();
    	if( me->query_temp("hit") )
    		damage = damage + me->query_skill("kugu-blade",1);
    	if( weapon )
    		message_vision(RED"\n�����ţ�$N��ʽһ�䣬"+weapon->name()+RED"�Ϸ�����ǧ�أ����ؽ���������Ѫ����ɫ��\n" NOR, me,target);
    	else
    		message_vision(RED"\n�����ţ�$N��ָ����һ��Ѫɫ������ֱ��$n��\n" NOR, me,target);
    	if( random(enhance) > random(target->query_skill("force",1) /3) &&
            random(me->query("combat_exp")) > random(target->query("combat_exp") /4) )
        {
        	me->add("force",-damage/3);
        	damage = damage + random(damage/2);
        	target->receive_damage("kee",damage,me);
        	target->receive_wound("kee",damage,me);
        	message_vision(HIR"\n���ֻ����$nһ���Һ��������Ѵ�$n�����϶Դ���������������Ѫ�꣡\n" NOR, me,target);
        	if( me->query("daojian_known") > 2 ) me->add_temp("hit",1);
        	COMBAT_D->report_status(target,1);
        	if( me->query("lunhui_zhuanshi") > 3 )
        		call_out("unarmed_attack",1,me,target);
        	else if( me->query("lunhui_zhuanshi") > 2 )
        		call_out("unarmed_attack",2,me,target);
        	else
        		call_out("unarmed_attack",3,me,target);
        	message_vision(RED"\n����մȾ��$n����Ѫ��Ѫɫ��Ũ��\n" NOR, me,target);
        }
        else
        {
        	me->add("force",-80);
        	message_vision(HIB"$n˳��һת�������������Ȼ�����Ѫɫ������\n" NOR, me,target);
        	if( me->query("lunhui_zhuanshi") > 2 )
        		call_out("unarmed_attack",1,me,target);
        	else
        		call_out("unarmed_attack",2,me,target);
        }
        message_vision(RED"\nѪɫ�������˸���ת����$N���Źඥ���룡\n" NOR, me);
        if (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0))  
        {
        	str=target->name()+HIM"��"+me->name()+"ץ�����飬���޶�����";
	        message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
	}
	return ;
}

void unarmed_attack(object me, object target)
{
	int enhance, damage;
	object weapon;
	string str;
	if( !me ) return ;
	if( !target ) target = offensive_target(me);
      	if( !target || !target->is_character()||target->is_corpse()||target==me ) return ;
      	if( !target->is_fighting(me) ) return ;
      	if( (int)me->query("force", 1) < 1000 )
        {
        	message_vision(HIB"$N�������㣬�������У�\n"NOR,me);
        	return ;
        }
      	weapon = me->query_temp("weapon");
      	enhance = me->query_skill("huntian-qigong",1);
    	damage = me->query_skill("yinfeng-zhua",1);
    	if( me->query_temp("hit") == 2 )
    		damage = damage + me->query_skill("kugu-blade",1) + me->query_skill("qixiu-jian",1);
    	if( me->query_temp("hit") == 1 )
    		damage = damage + me->query_skill("kugu-blade",1);
    	damage = damage + me->query_str();
    	if( weapon )
    		message_vision(RED"\n$N˫Ŀ���࣬"+weapon->name()+RED"�ϵ�����ѪӰ��������һ���޴��"+BLINK+HIR"Ѫצ"+NOR+RED"����$n����ץȥ��\n" NOR, me,target);
    	else
    		message_vision(RED"\n$N˫Ŀ���࣬��צ����Ҫ�γ�Ѫ����$Nһ�����У���צ����һƬѪӰ��������$n����ץ�£�\n" NOR, me,target);
    	if( random(enhance) > random(target->query_skill("force",1) /3) &&
            random(me->query("combat_exp")) > random(target->query("combat_exp") /4) )
        {
        	me->add("force",-damage/3);
        	damage = damage + random(damage/2);
        	target->receive_damage("kee",damage,me);
        	target->receive_wound("kee",damage,me);
        	message_vision(HIR"\nֻ����һ�󡸿��꡹���죬$n�������Ѿ���$Nץ�飡\n" NOR, me,target);
        	COMBAT_D->report_status(target,1);
        }
        else
        {
        	me->add("force",-100);
        	message_vision(HIB"����$n����һ���������$N�����һ������\n" NOR, me,target);
        }
        me->delete_temp("hit");
        if (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0))  
        {
        	str=target->name()+HIM"��"+me->name()+"ץ�����飬���޶�����";
	        message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
	}
	return ;
}