//sanban, �޵����師
//created 6-10-97 pickle
 
#include <ansi.h>
 
inherit SSERVER;

int perform(object me, object target)
{
  string msg,str,targetrude;
  int success,hurt,diff,damage;
  int delay;
  int myexp=(int)me->query("combat_exp")/5000;
  int mylev=(int)me->query_skill("axe");
  int mystr=(int)me->query("str")+(int)(me->query_skill("unarmed")/10-2);
  int mykar=(int)me->query_kar();
  int targetlev, targetstr,targetkar,targetexp,targeteffkee;
  string *hitone = ({
    "$n��ͼ����ܿ�����Ϊʱ���������ڼ��ϣ�����һ����ɼ��ǵ��˿ڣ�\n",
    "$n�߾����б�����ͼ�ܿ���������ס$N�����ƣ�������³�һ����Ѫ��\n",
    "$n�Թ�Ϊ�أ���ȥ�Ʋ�����������Ƶ�$N�ظ��Ի�����������$n������һ���˿ڡ�\n",
  });
  string *missone = ({
    "$n����һ�����󸫴���һ�󾢷�����ն�£���û�˵�$n�ֺ���\n",
    "$n�߾����б��з���һ�ܣ�ֻ����������һ�����죬$N�޸��ѱ�������\n",
    "$n���˴����ƣ�������$N�������Ƶ�$N���ò��ظ��Ա�����һ�ơ����ϡ��ʹ���ա�\n",
  });
  string *hittwo = ({
    "$n�ƺ�û�о���Σ�գ�˳��һ����������������֮����Ϊʱ���������Ѷ���һ�����糤���˿ڣ�\n",
    "$nû���$N�������֮�죬��æ��ͷ���ܣ����޷��㿪�������л���Ƥ��������\n",
    "$n������Ȼ�������������ط������ϱ����һƬƤ����Ȼ�˵ò��ᣡ\n",
  });
  string *misstwo = ({
    "$n�Դ�΢΢һ�࣬�ܹ���$N�Ĺ��ơ�\n",
    "$n�ƺ������ϵ���һ�У�˳���ڸ�����һ�ƣ����˿�ȥ��\n",
    "�ۿ�����Ҫ��$n�Դ������Դ���ͻȻ��$nʹ�������ţ����ֵ����˸��ա�\n",
  });
  string *hitthree = ({
    "$n�ƺ��ѱ����������������������˵�������ɢɢ��һ�ᣬ���󸫺����ڼ�ͷ��\n",
    "$n��׼���ƣ������б�����ȥ�������������ģ�����ͷ��û��ڳ�Ѫ����Ȼ���˲��ᣡ\n",
    "$n�ۼ�������������ͼ��ͷ�ܹ��������ϴ�������������$n���ϸ���һ��ƬƤ�⣡\n",
  });
  string *missthree = ({
    "$n�ƺ�������֪����·����δ������������ƮƮ�رܿ��ˡ�\n",
    "$n�ۼ��㲻�����У���æ�ڵ���һ������Ȼ�ܵ��Ǳ�����˿��û�����ˡ�\n",
    "$n��������Σ�գ��й�ֱ������$N��ȥ����Ȼ�����л����ˡ�\n",
  });
  string *hit=({
    RED"$N����Ҳ���㳢�����޵����師��������\n"NOR,
    RED"���޵����師һ���ǳɣ�$n�����˸����ֲ�����������Ϊ���£�\n"NOR,
    RED"$N��Ц������ƾ����㱾�£�Ҳ�����Ҷ���\n"NOR,
  });
  string *miss;
  
  if( !target ) target = offensive_target(me);
  if(me->query("family/family_name")!="������")
                return notify_fail("�㲻�ǽ��������ӣ�����ʹ������ܣ�\n");
  if( !target
     ||      !target->is_character()
     ||      !me->is_fighting(target) )
    return notify_fail("�޵����師�������źÿ��ģ�ֻ�ܶ�ս������ʩ�á�\n");
  targetrude=RANK_D->query_self_rude(target);
  targetexp=(int)target->query("combat_exp")/5000;
  targetlev=(int)target->query_skill("parry");
  targetstr=(int)target->query("str")+(int)(target->query_skill("unarmed")/10-2);
  //targetkar=(int)target->query_kar();
  miss=({
    BLU"$n������Ц����"+targetrude+"��˵���޵����師�ж�������������һ����Ҳ��������\n"NOR,
    BLU"$n��Цһ������$N��м��˵��������㱾�£�"+targetrude+"��û�������\n"NOR,
    BLU"$n�����Ц��������ʲô���£������ó����ɣ�\n"NOR,
  });
  if((string)me->query_skill_mapped("force")!="lengquan-force")
    return notify_fail("�޵����師��������Ȫ��Ϊ���ӡ�\n");
  if(me->query_skill("lengquan-force",1) < 50)
    return notify_fail("����ڹ����Ӳ��㣬�޷��˸���磬ʩչ�����޵����師��\n");
  if(me->query_skill("sanban-axe",1)<50)
    return notify_fail("�����������������Ϥ���޷�һ���ǳɵ�ʹ����\n");
  if(me->query("max_force") < 500 || me->query("force")<500)
    return notify_fail("����������㣬��������Ӷ�һ���󸫡�\n");
  if( time()-me->query_temp("sanban_end") < 5 )
  	return notify_fail("�����ö��ˣ��Ͳ����ˣ�\n");
  me->set_temp("sanban_end",time());
  msg = CYN "$Nһ�����ȣ����ϣ��������Ͷ��䣡����һ���ǳɣ�\n\nֻ��һ����Ӱ��������ֱ��$n���ţ�\n" NOR;
  if( random(myexp+targetexp) > targetexp/2)
    {
      msg += hitone[random(sizeof(hitone))];
      success+=1;
    }
  else msg+=missone[random(sizeof(missone))];
  msg+=CYN"\n$N���Ѿ�������˳���Ը�β���ּ⵶����$n���ţ�\n"NOR;
  if( random(mylev+targetlev) > targetlev/2)
    {
      msg += hittwo[random(sizeof(hittwo))];
      success+=1;
    }
  else msg+=misstwo[random(sizeof(misstwo))];
  msg+=CYN"\n$NѸ�����׵ط�ת��ͷ������$n�Դ�������ȥ��\n"NOR;
  if(random(mystr+targetstr)>targetstr/2)
    {
      msg+=hitthree[random(sizeof(hitthree))];
      success+=1;
    }
  else msg+=missthree[random(sizeof(missthree))];
  me->add("force", -(40+20*success));
  damage = mylev + random(mystr);
  damage = damage * (success * 2 + 1) / (success + 1);
    
  if(success)
    {
      damage = damage - random(target->query_temp("apply/armor"));
     if( damage < mylev ) damage = mylev;
     if( wizardp(me) ) tell_object(me,"damage:"+damage+"\n");
     target->receive_damage("kee", damage,me);
     damage = damage / 3;
     if( wizardp(me) ) tell_object(me,"wound:"+damage+"\n");
     target->receive_wound("kee", damage,me);

      delay = random(5-(mykar+5)/10);
      if( delay > 0 ) me->start_busy(delay);
      msg+=hit[random(sizeof(hit))];
    }
  else
    {
      delay = random(4-(mykar+5)/10);
      if( delay > 0 ) me->start_busy(delay);
      msg+=miss[random(sizeof(miss))];
    }
  message_vision(msg, me, target);
  if( (target->query("eff_kee")<0 || (!living(target) && target->query("kee")<0)) && !random(5) )
{str=target->name()+HIM"��"+me->name()+"�ý�����"NOR+HIR"���޵����師��"+HIM"�����ˣ���˵"+target->name()+"ʬ�屻����Ѫ��ģ����";
message("channel:rumor",HIM"����Ѩ���硿ĳ�ˣ�"+str+"\n"NOR,users());
}
  return 1;
}
