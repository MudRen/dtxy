// by canoe ,05-13-2001
// ������ȷʵ����
// ���pfm��cool
#include <ansi.h>
inherit SSERVER;

string begin_msg(object me,object target,int i,string w_name);
int perform(object me,object target)
{

string *l_weapon = ({
	"dodge",
	"unarmed",
	"sword",
	"blade",
	"staff",
	"hammer",
	"whip",
	"spear",
	"stick",
	"fork",
	"axe",
	"mace",
});
string *fail_msg = ({
	"����$nȴ�Ҵ�һͨ�������ײ����Ȼ��$N���಼�ɵ����ƻ��ˣ�\n",
	"����$N��ȭͷҪ����$n��˲�䣬$n��Ȼ�����һ����$Nһ�ܾ���һ�����˻�����\n",
	"��֪$n�����ϵ����У�ƾ��һ��������һԽ���ϣ���Ǵ���֮�����˳�ȥ\n",
	"$n��Ȼ�������ԵĻ����ǻ�Ӱ��˿������$N��Ӱ������Ӱ�죮\n",
	"�벻��$n�������Լ�����һ�ƣ���ǿ�ʹ���ȶ����Լ�����\n",
	"$n����˸գ����������������$N������һ��֮����Ϊ���У�\n",
});
string *succ_msg = ({
       "$nֻ��������������֮�����Լ�ѹ�������ζ�ʱ����������\n",
       "$n����ˣ�������޿��ˣ�Ӳ�����Ľ���$Nһȭ��ֻ������������������λ��\n",
       "$nһʱ������ֻ�������͡�������ԭ���Ѿ����������������˺����ۣ�\n",
       "$n�����޴룬���һ��������ز���$n���������ܵ��˺ܴ�Ĵ����\n",
       "$n���ܲ��˹��������ֻ���˹��ֿ���Ԫ������\n",
       "$n������ϸ�룬ƾ�о����������������ˣ������Ǳ����У���ʱ�ж�����\n",
});
	object weapon,temp;
	int ap,dp,flag,i,damage;
	string *w_temp,w_name;
	string msg;

	string unarmed,dodge,staff,hammer,sword,blade;
	if(!target)      target = offensive_target(me);
	if((string)me->query("family/family_name") != "��ׯ��" )
		return notify_fail("�㲻����Ԫ���£������������˴��С���Ȼ��ɡ���\n");
	
	if(!target
	|| !target->is_character()
	|| target->is_corpse()
	|| target == me )
		return notify_fail("��׼����˭�����С���Ȼ��ɡ���\n");
	
	if(!me->is_fighting(target))
		return notify_fail("��һ�С���Ȼ��ɡ�������ս���в���ʹ�ã�\n");
	if( me->query("sen") < 500 )
		return notify_fail("��ľ����㣬ʹ�����С���Ȼ��ɡ�������Σ�գ�\n");
	if( me->query("kee") < 500 )
	 return notify_fail("�����Ѫ���㣬ʹ�����С���Ȼ��ɡ�������Σ�ա�\n");
		 
	if( me->query("max_force") < 600 )
		return notify_fail("�����������������ʹ�����С���Ȼ��ɡ���\n");
	if( me->query("force") < 1500 )
		return notify_fail("��ĵ�ǰ����̫���ˣ�����Σ�յģ�\n");
	if( me->query("mana") < 1800 )
		return notify_fail("��ĵ�ǰ����̫�ͣ����޷������������С�\n");
	if( me->query_skill("zhenyuan-force",1) < 100 )
		return notify_fail("�����Ԫ�񹦼���̫�ͣ����ò������У�\n");
	if( me->query_skill("taiyi",1) < 120 )
		return notify_fail("���̫���ɷ�����̫�ͣ������˴��У�\n");
	if( me->query_skill("sanqing-jian",1) < 100 )
		return notify_fail("������彣����̫�ͣ�ʹ�����п�����Σ�գ�\n");
	if( me->query_skill("kaishan-chui",1) < 100 )
		return notify_fail("��Ŀ�ɽ������̫�ͣ����ò������У�\n");
	if( me->query_skill("fumo-zhang",1) < 100 )
		return notify_fail("��ķ�ħ�ȼ���̫�ͣ����ò������У�\n");
		
	weapon = me->query_temp("weapon");
	unarmed = me->query_skill_mapped("unarmed");
	sword = me->query_skill_mapped("sword");
	staff = me->query_skill_mapped("staff");
	hammer = me->query_skill_mapped("hammer");
	blade = me->query_skill_mapped("blade");
	dodge = me->query_skill_mapped("dodge");
	if( unarmed == "wuxing-quan" )  flag = 1;
	if( sword == "sanqing-jian" )  flag += 1;
	if( staff == "fumo-zhang" )    flag += 1;
	if( hammer == "kaishan-chui" )  flag += 1;
	if( blade == "yange-blade" )   flag += 1;

	if( flag < 3 )
		return notify_fail("�㱾���书̫�٣��޷�ʹ�����С���Ȼ��ɡ���\n");
	if( me->query_skill_mapped("force") != "zhenyuan-force" )
		return notify_fail("û����Ԫ��������������������С���Ȼ��ɡ���\n");
	if( me->query_skill_mapped("spells") != "taiyi" )
		return notify_fail("û��̫���ɷ���������ν����С���Ȼ��ɡ����ӵ�����޶ȣ�\n");
	msg = HIR"\n$N����̫�����ԣ��������Ȼ���������������ԽתԽ�죬������Խ��Խ�ݣ�������\n"NOR;
	message_vision(msg,me);
	me->start_busy(2+random(3));
	me->add("force",-400);
	me->add("mana",-300);
	for(i=0;i<sizeof(l_weapon);i++)
	{
	seteuid(getuid());
	if( !me->query_skill_mapped(l_weapon[i]) ||(int)me->query_skill(me->query_skill_mapped(l_weapon[i]),1) < 100 )
		continue;
	if(l_weapon[i]=="unarmed")
	{
		w_name = " ";
		msg = begin_msg(me,target,i,w_name);
	}
	else
	if(l_weapon[i]=="dodge")
	{
		w_name = " ";
		msg = begin_msg(me,target,i,w_name);
	}
	else
	{
	if(l_weapon[i]=="sword") temp=new("/d/obj/weapon/sword/ruler"); 
        if(l_weapon[i]=="hammer") temp=new("/d/obj/weapon/hammer/tongchui"); 
        if(l_weapon[i]=="blade") temp=new("/d/obj/weapon/blade/gudingdao"); 
        if(l_weapon[i]=="staff") temp=new("/d/obj/weapon/staff/budd_staff"); 
        temp->move(me);
	w_name = temp->query("name");
	msg = begin_msg(me,target,i,w_name);
	if ( i >= 6 || msg== "shake" )
         {      weapon->delete("equipped");
                temp->set("equipped","wielded");
                me->set_temp("weapon",temp);
                me->reset_action();
		message_vision(msg,me,target);
                COMBAT_D->do_attack(me,target,me->query_temp("weapon"));
                temp->delete("equipped");
                weapon->set("equipped","wielded");
                me->set_temp("weapon",weapon);
                destruct(temp);
                me->reset_action();
		continue;
	}
	}
        message_vision(msg,me,target);
	if(temp)
	destruct(temp);

	ap = me->query_skill(l_weapon[i]) + me->query_skill("force") + me->query_skill("spells") + me->query("combat_exp")/20000 + me->query_skill("literate");
	dp = target->query_skill("parry") + target->query_skill("force") + target->query_skill("dodge") + target->query("combat_exp")/20000;
	if( random(ap) < random(dp) && userp(target) )
	{	message_vision(fail_msg[i],me,target);
	}
	else
	if( random(ap) < random(dp*2/3) && !userp(target) )
	{       message_vision(fail_msg[i],me,target);
	}
	else
	{
		if( l_weapon[i] == "dodge" )
		{me->add_temp("apply/dodge",(int)me->query_skill("dodge",1)/2);
		 me->add_temp("apply/attack",(int)me->query_skill("dodge",1)/2);
		 me->add_temp("apply/armor",(int)me->query_skill("dodge",1)/2);
		 me->add_temp("apply/strength",(int)me->query_skill("dodge",1)/2);
		target->add_temp("apply/dodge",-(int)me->query_skill("dodge",1)/2);
			me->set_temp("apply/dodge_add",1);
			message_vision(succ_msg[i],me,target);
			me->reset_action();
			continue;
		}		
		if( l_weapon[i] == "unarmed" )
		{	
			target->receive_damage("kee",me->query_skill("unarmed")/(1+random(2)));
			target->receive_wound("kee",me->query_skill("unarmed")/(2+random(2)));
			target->set_temp("last_damage_from",me);
			if(target->query("force")>me->query_skill("unarmed")*2)
			target->add("force",-me->query_skill("unarmed")*2);
			else target->set("force",1);
			if(me->query("force")<3*me->query("max_force"))
			me->add("force",me->query_skill("unarmed"));
			message_vision(succ_msg[i],me,target);
			COMBAT_D->report_status(target);
			continue;
		}
		weapon->delete("equipped");
		if(l_weapon[i]=="sword") temp=new("/d/obj/weapon/sword/ruler"); 
        	if(l_weapon[i]=="hammer") temp=new("/d/obj/weapon/hammer/tongchui"); 
        	if(l_weapon[i]=="blade") temp=new("/d/obj/weapon/blade/gudingdao"); 
        	if(l_weapon[i]=="staff") temp=new("/d/obj/weapon/staff/budd_staff"); 
 		temp->move(me);
		temp->set("equipped","wielded");
 		me->set_temp("weapon",temp);
		me->reset_action();
		message_vision(succ_msg[i],me,target,me->query_temp("weapon"));

		damage = me->query_skill(l_weapon[i]) + random(me->query_skill(l_weapon[i])) + me->query("force_factor");
		if(random(5)==1)
		{damage += me->query_str();
		message_vision(CYN"\n��!!��!!��!!$N��$n�ҵ�������ת,վ������,���ȥ��������!!\n",target,me->query_temp("weapon")); }
		target->receive_damage("kee",damage/(2+random(2)));
		target->receive_wound("kee",damage/(5+random(3)));
		target->receive_damage("sen",damage/4);
		target->receive_wound("sen",damage/8);
		target->set_temp("last_damage_from",me);
	        COMBAT_D->report_status(target);
        	temp->delete("equipped");
        	weapon->set("equipped","wielded");
        	me->set_temp("weapon",weapon);
        	destruct(temp);
        	me->reset_action();

	}
	}	
	if(me->query_temp("apply/dodge_add"))
	{
		me->add_temp("apply/dodge", -(int)me->query_skill("dodge",1)/2);
		me->add_temp("apply/attack",-(int)me->query_skill("dodge",1)/2);
		me->add_temp("apply/armor",-(int)me->query_skill("dodge",1)/2);
		me->add_temp("apply/strength",-(int)me->query_skill("dodge",1)/2);
		target->add_temp("apply/dodge",(int)me->query_skill("dodge",1)/2);
		me->delete_temp("apply/dodge_add");
	}		 
       if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }
	return 1;
}
string begin_msg(object me,object target,int i,string w_name)
{
 	if(i==0)	
           return ( HIM"\n������������������������������Ű��ԡ�"NOR+"\n$N���������Ǭ���죬�����أ��������Σ���ת��ʼ������$nԽתԽ�죬\nͬʱ�ڵ��ϲ�֪����һЩʲô����.��������Щ����ı仯!!!\n");
	if(i==1)
         return ( HIC"\n�����о���������������������������ˡ�"NOR+"\n$N�е�����ľ��ˮ����������ͬʱ��˫�ֽ�����ȭ��һȭ��һȭ�죬������\n�����Ī��֮���ƣ�������֮��ӵ����쾡�£�ֱ����$n��ȥ��\n");
	if(i==2)
       return ( HIY"\n�����־��������������������������طɡ�"NOR+"\n$N������"+w_name+"������һ�ף���ָ$n���е���ȥҲ��ֻ��"+w_name+"һ�ֶ���\n�����ģ�Խ��Խ�࣬������˷�ֱ����$n��ȥ,$n��ʱ����ʧ�룮\n");
	if(i==3)
        return (HIR"\n�����־�����������������������ԡ������"NOR+"\n$N���������︽����"+w_name+"�ϣ������������˼��£�����֮�������������棬\n����Ҫ��$n����һ��,$n����������ӳ��ͨ�죮\n");
	if(i==4)
       return (HIB"\n�����־���������������������������ħ��"NOR+"\n$N����"+w_name+",��������̫�����ԣ�$nֻ���ĵ׷��겻�ѣ�\n");
	if(i==5)
        return (HIW"\n�����־������������������������춯�ء�"NOR+"\n$N˫�־���"+w_name+"�����������֮����$n��ȥ�����п��ƴ�׾��ʵ����ɣ�\n"+w_name+"�ڿ���һ��ת��,��$n����,$n����д���ֲ�!\n");
	if(i==6)
	return (HIG"\n���־�����������������������������"NOR);
	if(i==7)
	return (HIR"\nǹ�־�����������������������ս��ʤ"NOR);
	if(i==8)
	return (HIY"\n���־�����������������������������"NOR);
	if(i==9)
	return (HIB"\n���־����������������������ĺ�ƽ��"NOR);
	if(i==10)
	return (HIW"\n���־�������������������������ɽ��"NOR);
	if(i==11)
	return (HIR"\n��־�����������������������ɨǧ��"NOR);
	return ("shake");

}
