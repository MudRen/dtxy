// tian.c by single
//this perform have too large damage, aqing medifyed it
//and solved the nk problem
// aqing 2000.9.30
// �޸�by canoe ,05-13-2001
// ����������,������ȷʵ����,��С��
// ���pfm��cool
#include <ansi.h>
inherit SSERVER;

string begin_msg(object me,object target,int i,string w_name);
int perform(object me,object target)
{

string *l_weapon = ({
	"dodge",
	"unarmed",
	"spear",
        "archery",
	"axe",
	"mace",
	"mace",
});
string *fail_msg = ({
	"����$nȴ�Ҵ�һͨ�������ײ����Ȼ��$N���಼�ɵ����ƻ��ˡ�\n",
	"����$N��ȭͷҪ����$n��˲�䣬$n��Ȼ�����һ����$Nһ�ܾ���һ�����˻�����\n",
	"$n��Ȼ�������ԵĻ����ǻ�Ӱ��˿������$N��Ӱ������Ӱ�졣\n",
	"��֪$n�����ϵ����У�ƾ��һ��������һԽ���ϣ���Ǵ����֮�����˳�ȥ��\n",
	"$n��æ�������Ծ�����ɣ�����ǿ������������һ����\n",
	"$n����˸գ����������������$N������һ��֮����Ϊ���С�\n",
	"�벻��$n��ת�ķ���Ӳ�ǿ�����$N���ɰٴ��ľ�ѧ��\n",
});
string *succ_msg = ({
       "$nֻ��������������֮�����Լ�ѹ�������ζ�ʱ����������\n",
       "$n����ˣ�������޿��ˣ�Ӳ�����Ľ���$Nһȭ��ֻ������������������λ��\n",
       "$n�����޴룬���һ��������ز���$n���������ܵ��˺ܴ�Ĵ����\n",
       "$nһʱ������ֻ�������͡�������ԭ���Ѿ��������������ǧ����ס�\n",
       "���һ�������$n��ͷ����,����һ����Ѫ��\n",
       "$n������ϸ�룬ƾ�о����������������ˣ������Ǳ����У���ʱ�ж�����\n",
       "$n�ֵ���ס��ƴ��ҧ����⣬����Ǳ��ƽϢ�˾�����ɧ����\n",
});
	object weapon,temp;
	int ap,dp,flag,i,damage,damage_flag;
	string *w_temp,w_name;
	string msg;

    	string str; 
	string unarmed,dodge,axe,mace,spear,archery;
	int cd = 8;
	if(!target)      target = offensive_target(me);
	if(!wizardp(me)&&(string)me->query("family/family_name") != "������" )
		return notify_fail("�㲻�ǽ��������£������������˴��С���Ȼ��ɡ���\n");
	
	if( me->query("lunhui_zhuanshi") > 1 )
		cd = 6;
	else if( me->query("lunhui_zhuanshi") )
		cd = 7;
	if( time()-(int)me->query_temp("xiao_end") < cd )
		return notify_fail("�����ö�Ͳ����ˣ�\n");
	if(!target
	|| !target->is_character()
	|| target->is_corpse()
	|| target == me )
		return notify_fail("��׼����˭�����С���Ȼ��ɡ���\n");
	
	if(!me->is_fighting(target))
		return notify_fail("����Ȼ��ɡ�������ս���в���ʹ�ã�\n");
	if( me->query("sen") < 500 )
		return notify_fail("��ľ����㣬ʹ�����С���Ȼ��ɡ�������Σ�գ�\n");
	if( me->query("kee") < 500 )
	 return notify_fail("�����Ѫ���㣬ʹ�����С���Ȼ��ɡ�������Σ�ա�\n");
		 
	if( me->query("max_force") < 1200 )
		return notify_fail("�����������������ʹ�����С���Ȼ��ɡ���\n");
	if( me->query("force") < 800 )
		return notify_fail("��ĵ�ǰ����̫���ˣ�����Σ�յģ�\n");
	if( me->query("mana") < 800 )
		return notify_fail("��ĵ�ǰ����̫�ͣ����޷������������С�\n");
	if( me->query_skill("lengquan-force",1) < 100 )
		return notify_fail("�����Ȫ�񹦼���̫�ͣ����ò������У�\n");
	if( me->query_skill("baguazhou",1) < 120 )
		return notify_fail("��İ����伶��̫�ͣ������˴��У�\n");
	if( me->query_skill("spear",1) < 100 )
		return notify_fail("��Ļ���ǹ����̫�ͣ�ʹ�����п�����Σ�գ�\n");
	if( me->query_skill("mace",1) < 100 )
		return notify_fail("��Ļ���ﵷ�����̫�ͣ����ò������У�\n");
	if( me->query_skill("axe",1) < 100 )
		return notify_fail("��Ļ�����������̫�ͣ����ò������У�\n");
		
	weapon = me->query_temp("weapon");
	unarmed = me->query_skill_mapped("unarmed");
	spear = me->query_skill_mapped("spear");
	axe = me->query_skill_mapped("axe");
	mace = me->query_skill_mapped("mace");
	archery = me->query_skill_mapped("archery");
	dodge = me->query_skill_mapped("dodge");
	if( unarmed == "changquan" )  flag = 1;
	if( spear == "bawang-qiang" )  flag += 1;
	if( axe == "sanban-axe" )    flag += 1;
  if( mace == "jinglei-mace" )  flag += 1;
	if( archery == "xuanyuan-archery" )   flag += 1;

	if( flag < 3 )
		return notify_fail("�㱾���书̫�٣��޷�ʹ�����С���Ȼ��ɡ���\n");
	if( me->query_skill("wusi-mace",1) > 120 ) flag += 1;
	if( me->query_skill_mapped("force") != "lengquan-force" )
		return notify_fail("û����Ȫ��������������������С���Ȼ��ɡ���\n");
	if( me->query_skill_mapped("spells") != "baguazhou" )
		return notify_fail("û�а�������������ν����С���Ȼ��ɡ����ӵ�����޶ȣ�\n");
	msg = HIR"\n$N��������䣬�������Ȼ���������������ԽתԽ�죬������Խ��Խ�ݣ�������\n"NOR;
	message_vision(msg,me);
//	me->start_busy(2+random(3));
	me->add("force",-400);
	me->add("mana",-300);
	if(userp(target))
		damage_flag = 0;
	else
		damage_flag = 1;
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
		if(l_weapon[i]=="spear") temp=new("/d/obj/weapon/spear/biyuqiang"); 
        	if(l_weapon[i]=="axe") temp=new("/d/obj/weapon/axe/huafu"); 
           	if(l_weapon[i]=="mace") temp=new("/d/obj/weapon/mace/goldjian"); 
		if(l_weapon[i]=="archery") temp=new("/d/obj/weapon/archery/mugong"); 
        	temp->move(me);
		w_name = temp->query("name");
		msg = begin_msg(me,target,i,w_name);
	/*if ( i >= 6 || msg== "shake" )
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
	}*/
	}
        message_vision(msg,me,target);
	if(temp)
	destruct(temp);

	ap = me->query_skill(l_weapon[i], 1) + me->query_skill("force", 1) + me->query_skill("spells", 1);
	dp = target->query_skill("parry", 1) + target->query_skill("force", 1) + target->query_skill("dodge", 1);
    if (userp(me)) ap += me->query_skill("literate",1);
	if( !userp(target) )//�Թ�����������
		dp = dp*2/3;
	//if( random(ap) < random(dp*2/3) && userp(target) )
	//{	message_vision(fail_msg[i],me,target);
	//}
	//else
	if( random(ap + dp/2) < dp/2 )//&& !userp(target) )
	{       message_vision(fail_msg[i],me,target);
	}
	else
	{
		if( l_weapon[i] == "dodge" )
		{
			//me->add_temp("apply/dodge",(int)me->query_skill("dodge",1)/3);
		 	//me->add_temp("apply/attack",(int)me->query_skill("dodge",1)/3);
		 	//me->add_temp("apply/armor",(int)me->query_skill("dodge",1)/3);
		 	me->add_temp("apply/strength",(int)me->query_skill("dodge",1)/3);
			target->add_temp("apply/dodge",-(int)me->query_skill("dodge",1)/4);
			target->add_temp("apply/parry",-(int)me->query_skill("dodge",1)/4);
			me->set_temp("apply/dodge_add",1);
			message_vision(succ_msg[i],me,target);
			me->reset_action();
			continue;
		}		
		if( l_weapon[i] == "unarmed" )
		{
			message_vision(succ_msg[i],me,target);	
			damage = me->query_skill(l_weapon[i]) * (5+me->query("kai_known")) / 5 + random(me->query_skill(l_weapon[i]))/3;// + me->query("force_factor");
	                if(random(ap) > dp/2)
        	        {
                	        damage += me->query_str() + damage / 3;
                        	message_vision(CYN"\n��!!��!!��!!$N��$n�ҵ�������ת,վ������,���ȥ��������!!\n"NOR,target,me->query_temp("weapon"));
	                }
        	        target->receive_damage("kee",damage/(1+damage_flag));
                	target->receive_wound("kee",damage/(2+damage_flag));
	                target->receive_damage("sen",damage/3);
	                target->receive_wound("sen",damage/6);
        	        target->set_temp("last_damage_from",me);
			COMBAT_D->report_status(target);
			COMBAT_D->report_sen_status(target, 0);
			continue;
		}
		weapon->delete("equipped");
	        if(l_weapon[i]=="spear") temp=new("/d/obj/weapon/spear/biyuqiang"); 
        	if(l_weapon[i]=="axe") temp=new("/d/obj/weapon/axe/huafu"); 
	        if(l_weapon[i]=="mace") temp=new("/d/obj/weapon/mace/goldjian"); 
        	if(l_weapon[i]=="archery") temp=new("/d/obj/weapon/archery/mugong"); 
	 	temp->move(me);
		temp->set("equipped","wielded");
	 	me->set_temp("weapon",temp);
		me->reset_action();
		message_vision(succ_msg[i],me,target,me->query_temp("weapon"));

		damage = me->query_skill(l_weapon[i]) * (5+me->query("kai_known")) / 5 + random(me->query_skill(l_weapon[i]))/3;// + me->query("force_factor");
		if(random(ap) > dp/2)
		{
			damage += me->query_str() + damage / 3;
			message_vision(CYN"\n��!!��!!��!!$N��$n�ҵ�������ת,վ������,���ȥ��������!!\n"NOR,target,me->query_temp("weapon")); 
		}
             	target->receive_damage("kee",damage/(1+damage_flag));
                target->receive_wound("kee",damage/(2+damage_flag));
		target->receive_damage("sen",damage/3);
		target->receive_wound("sen",damage/6);
		target->set_temp("last_damage_from",me);
	        COMBAT_D->report_status(target);
		COMBAT_D->report_sen_status(target, 0);
        	temp->delete("equipped");
        	weapon->set("equipped","wielded");
        	me->set_temp("weapon",weapon);
        	destruct(temp);
        	me->reset_action();

	}
	}	
	if(me->query_temp("apply/dodge_add"))
	{
		//me->add_temp("apply/dodge", -(int)me->query_skill("dodge",1)/3);
		//me->add_temp("apply/attack",-(int)me->query_skill("dodge",1)/3);
		//me->add_temp("apply/armor",-(int)me->query_skill("dodge",1)/3);
		me->add_temp("apply/strength",-(int)me->query_skill("dodge",1)/3);
		target->add_temp("apply/dodge",(int)me->query_skill("dodge",1)/4);
		target->add_temp("apply/parry",(int)me->query_skill("dodge",1)/4);
		me->delete_temp("apply/dodge_add");
	}		 
       /*if( !target->is_fighting(me) ) {
                if( living(target) ) {
                        if( userp(target) ) target->fight_ob(me);
                        else target->kill_ob(me);
                }
        }*/
    if( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )  
{str=target->name()+HIM"��"+me->name()+"�ý������ش�"NOR+HIR"����Ȼ��ɡ�"+HIM"�����ˣ���˵"+target->name()+"��ʬ�����������";
    message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
  }
    me->set_temp("xiao_end",time());
	return 1;
}
string begin_msg(object me,object target,int i,string w_name)
{
 	if(i==0)	
return (HIM"\n������������������������������Ű��ԡ�"NOR+"\n$N���������Ǭ���죬�����أ��������Σ���ת��ʼ������$nԽתԽ�죬\nͬʱ�ڵ��ϲ�֪����һЩʲô����.��������Щ����ı仯������\n");
	if(i==1)
return (HIC"\n���������������������������������޵С�"NOR+"\n$N�е������š�ͬʱ��˫�ֽ�����ȭ��һȭ��һȭ�죬������\n�����Ī��֮���ƣ�����ȭ���ӵ����쾡�£�ֱ����$n��ȥ��\n");
	if(i==2)
return (HIR"\n��ǹ�־����������������������ǻ���ԭ��"NOR+"\n$N���������︽����"+w_name+"�ϣ������������˼��£�����֮�������������棬\n����Ҫ��$n����һ��,$n����������ӳ��ͨ�졣\n");
	if(i==3)
return (HIY"\n�����־�����������������������ս��ʤ��"NOR+"\n$N������"+w_name+"������һ�ף���ָ$n���е���ȥҲ��ֻ��"+w_name+"�������������\n����Խ��Խ�࣬������˷�ֱ����$n��ȥ,$n��ʱ����ʧ�롣\n");
	if(i==4)
return (HIB"\n�����־�������������������������ɽ�ӡ�"NOR+"\n $NͻȻ����һ����������"+w_name+"б���Ͼ���\nȻ���ڰ���л���һ��Բ�����漴��ֱб��ն��$n��\n");
	if(i==5)
return (HIW"\n�����׾�������������������������ŭ��"NOR+"\n$N˫�־���"+w_name+"�����������֮����$n��ȥ�����п��ƴ�׾��ʵ����ɡ�\n"+w_name+"�ڿ���һ��ת��,��$n����,$n����д���ֲ���\n");
	if(i==6)
return (HIG"\n����˽�������������������������ɰٴ���"NOR+"\n$N����"+w_name+"��������������䣬$N�ݷ����󺣣�����������$N����������\n$n��������������������֮����ɫ��ò԰ס�\n");
else return ("shake");
}
