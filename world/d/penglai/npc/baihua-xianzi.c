//Cracked by Roath

//baihua xianzi
inherit NPC;
inherit F_MASTER;
string ask_jueqing();
string ask_mojie();
void create()
{
       set_name("�ٻ�����", ({"baihua xianzi", "baihua", "xianzi"}));
       set("long",@LONG
����ĸ�ĵ��ӡ�����ĸ֮������˾������������Ⱥ��֮����
�����϶����������ݺ������ط����������������������
��㺮�����������ơ��ٻ���Ϊ�����˼䣬��һ��Һ��
LONG);

       set("title", "Ⱥ��֮��");
       set("gender", "Ů��");
       set("age", 20);
       set("class", "xian");
       set("attitude", "friendly");
       set("rank_info/respect", "�ɹ�");
       set("per", 30);
        set("int", 30);
       set("max_gin", 600);
  set("max_sen",3000);
  set("max_kee",3000);
   set("force",2000);
       set("max_force", 2000);
       set("force_factor", 100);
       set("max_mana", 2000);
       set("mana", 2000);
       set("mana_factor", 200);
       set("combat_exp", 800000);
       set("daoxing", 1200000);


   set("inquiry",([
   	"�ٻ���":"��ϧ����Ƨ�����⣬�滨Ʒ�ֲ�ȫ�������ھ��м���(add)�����ʻ����˾Ʋ�����ɡ�",
   	"����": (: ask_jueqing :),
   	"ħ��": (: ask_mojie :),
   	]));
        set("eff_dx", 200000);
        set("nkgain", 350);

       set_skill("literate", 100);
       set_skill("unarmed", 80);
       set_skill("dodge", 70);
       set_skill("force", 80);
       set_skill("parry", 80);
       set_skill("spells", 80);
       set_skill("moonshentong", 80);
       set_skill("baihua-zhang", 200);
       set_skill("moonforce", 80);
       set_skill("moondance", 70);
       set_skill("whip",80);
       set_skill("jueqingbian",80);
       map_skill("spells", "moonshentong");
       map_skill("unarmed", "baihua-zhang");
       map_skill("force", "moonforce");
       map_skill("dodge", "moondance");

           set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: cast_spell, "arrow" :),
               (: cast_spell,"mihun" :),
               (: cast_spell,"shiyue" :),
        }) );
       create_family("�¹�", 2, "����");
       setup();

       carry_object("/d/moon/obj/luoyi")->wear();
     carry_object("/d/obj/book/makeupbook");
      carry_object("/d/shendian/babu/obj/xiangjing");
       if (clonep()) carry_object("/d/obj/flower/rose")->wear();
}

void attempt_apprentice(object ob)
{
        if ( !((string)ob->query("gender")=="Ů��")){
           command("shake");
           command("say �����¹�ֻ��Ůͽ����λ" +
RANK_D->query_respect(ob) + "��������߾Ͱɡ�\n");
           return;}
        if ( !ob->query_temp("denied_by_chang_e")){
          command("shake");
        command("say ��ֻ����Ե֮�ˣ���λ" +
RANK_D->query_respect(ob) + "����ȥ����϶�ɡ�\n");
        return;
}

        command("pat "+ob->query("id"));
        command("say �ã�ϣ��" + RANK_D->query_respect(ob) +
"���Ŭ�����������¹�������\n");
        command("recruit " + ob->query("id") );
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )
                ob->set("class", "xian");
}
string ask_jueqing()
{
	object me=this_player();
	if(me->query("family/family_name") != "�¹�" )
                return ("�㲻�����¹�����!!\n");
        if( me->query("betray/count") )
		return ("�����Ķ����޷�����¹���ѧ��\n");
        if( (string)me->query("gender") !="Ů��")
                return ("���Ϊ����֮��,����֪��Ů���ҵ���˼??\n");
        if(me->query("jueqing_known"))
      		return ("�����аٻ��ƵĿھ��㶼�Ѿ�֪���˰���");
      	if(me->query("jueqing_cant"))
      		return ("���������Ե��");
      	if(me->query("jueqing/baihua"))
      		return ("�����аٻ��ƵĿھ��㶼�Ѿ�֪���˰���");
      	if( !me->query_temp("jueqing/baihua") )
      	{
      		me->set_temp("jueqing/baihua",1);
      		command("sigh");
	      	command("say ��������Ϊ���ֱ������������");
	      	return("����������ס����ô���ֻ꣬ΪѰ����Ҷ��֥�ݣ���ɰٻ������Ȼ���ģ��Ͱ���Ѱ����Ҷ��֥�ݣ�������(add)�ٻ����У�");
	}
	else if( me->query_temp("jueqing/baihua") == 2 )
	{
		return("�ۣ��ٻ�����������ˣ��϶�ʦ�����¿��Ժúܶ��ˣ�����Ͱ�����ȥ�ɣ��ǵÿ�ȥ��أ�");
	}
	else if( me->query_temp("jueqing/baihua") == 3 )
	{
		me->delete_temp("jueqing/baihua");
		me->set("jueqing/baihua",1);
		return("ʦ������ö��˰ɣ�����ǰٻ��ƵĿھ������ס�ˣ�");
	}
      	else
      	{
      		return("��ȥѰ����Ҷ��֥�ݰɣ�");
      	}
}

string ask_mojie()
{
	object me=this_player();
	if(me->query("family/family_name") != "�¹�" )
                return ("�㲻�����¹�����!!\n");
        if( me->query("betray/count") )
		return ("�����Ķ����޷�����¹���ѧ��\n");
        if( (string)me->query("gender") !="Ů��")
                return ("���Ϊ����֮��,����֪��Ů���ҵ���˼??\n");
      	if(me->query("jueqing_cant"))
      		return ("���������Ե��");
      	if( !me->query_temp("jueqing/binghun") )
      		return ("ʱ��δ����");
      	if( me->query_temp("jueqing/binghun") == 1 )
      	{
      		me->set_temp("jueqing/binghun",2);
	      	command("say ��Ȼ������˱��죬�Ǿ�ȥħ��ȡ�ر���ɡ�ʦ�õ������Ѿ�����������ȥ�ˣ�");
	      	command("say �㿴��ٻ����ļ��紺��������Ϊ�ٻ��ȵ��±��ǳ����ҽ������ħ�硣");
	      	command("say �����������治�У���������������֮�������ħ�硣");
	      	command("say ħ���ڵĹ���ʵ���Ƿ����׶�ö�������ʦ����֯Ů֯���߲��Ʋ����ٸ��԰ٻ���������ӡ��ħ��ͨ����");
	      	command("say ��������˳��ȡ�ñ��꣬ħ��ؽ�ʵ������֯ŮҲ����ţ������ˣ����ǹ�����������");
	      	command("say �����������϶�ʦ���Ի��֪���㣬����ʹ�ħ��ͨ����");
	      	return("��ӱ��������£�jump down���Ϳ��Ե���ħ�磬��ȡ�ñ����Ժ��Ի᷵�أ�");
	}
	else if( me->query_temp("jueqing/binghun") == 2 )
	{
		return("��ӱ��������£�jump down���Ϳ��Ե���ħ�磬��ȡ�ñ����Ժ��Ի᷵�ء��Ͻ�����ɣ�");
	}
	else
	{
		return("�Ͻ��������͸��϶�ʦ�ðɣ�");
	}
}