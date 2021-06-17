//change.c
inherit NPC;
inherit F_MASTER;
string ask_jueqing();
void destroy(object ob);
void create()
{
       set_name("�϶�", ({"chang e", "change", "chang","master"}));
       set("long",
"����ĸ�Ĵ���ӡ�����������ɷ��ȡ����ĸ֮��ҩ��\n����ʦ�Ƴ�ˮ�𡣺�úͽⲢ������ĸ�����¹�һ�š�\n");
       set("title", "�¹�����");
       set("gender", "Ů��");
       set("age", 20);
       set("class", "xian");
       set("attitude", "friendly");
       set("rank_info/respect", "�ɹ�");
       set("per", 30);
	set("int", 30);
       set("max_kee", 900);
       set("max_gin", 600);
       set("max_sen", 800);
       set("force", 800);
       set("max_force", 800);
       set("force_factor", 50);
       set("max_mana", 600);
       set("mana", 600);
       set("mana_factor", 40);
       set("combat_exp", 400000);
  set("daoxing", 800000);


        set("eff_dx", 200000);
        set("nkgain", 350);
	set("inquiry",([
      "����": (: ask_jueqing :),
      ]));
       set_skill("literate", 80);
       set_skill("unarmed", 80);
       set_skill("dodge", 180);
       set_skill("force", 80);
       set_skill("parry", 80);
       set_skill("sword", 80);
       set_skill("spells", 80);
        set_skill("moonshentong", 80);
        set_skill("baihua-zhang", 80);
        set_skill("moonforce", 80);
        set_skill("snowsword", 80);
        set_skill("moondance", 200);
        map_skill("spells", "moonshentong");
        map_skill("unarmed", "baihua-zhang");
        map_skill("force", "moonforce");
        map_skill("sword", "snowsword");
        map_skill("parry", "snowsword");
        map_skill("dodge", "moondance");

create_family("�¹�", 2, "����");
setup();

        carry_object("/d/moon/obj/luoyi")->wear();
        carry_object("/d/moon/obj/feijian")->wield();
}

void attempt_apprentice(object ob)
{
        if ( !((string)ob->query("gender")=="Ů��")){
           command("shake");
           command("say �����¹�ֻ��Ůͽ����λ" +
RANK_D->query_respect(ob) + "��������߾Ͱɡ�\n");
           return;}
        if ( (int)ob->query("per") <22){
	  command("shake");
	command("say ���ҿ���λ" +
RANK_D->query_respect(ob) + "�����ʲ����������裬��������߾Ͱɡ�\n");
  ob->set_temp("denied_by_chang_e",1);
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
int accept_object(object me,object ob)
{
       	if( me->query_temp("jueqing/chimeng") == 2 && ob->query("id") == "tongxin lianou" )
       	{
       		command ("say ��л���ˣ����ȥ�ҳ���ʦ��ɡ�ף�������������ޣ�");
       		me->set_temp("jueqing/chimeng",3);
       		call_out("destroy", 2, ob);
       		return 1;	
       	}
       	if( me->query_temp("jueqing/baihua") == 2 && ob->query("baihua") )
       	{
       		command ("say �ٻ�ʦ��������ɰٻ����ˣ�Ϊ���ҿ����ô�ҷѾ�����˼�ˣ����ȥ�Ұٻ�ʦ��ɣ��𹼸�����һƬ���⣡");
       		me->set_temp("jueqing/baihua",3);
       		me->set("leaf",ob->query("baihua"));
       		call_out("destroy", 2, ob);
       		return 1;	
       	}
       	if( me->query_temp("jueqing/binghun") == 3 && ob->query("id") == "bing hun" )
       	{
       		command ("say ��ô�����ˣ������õ��˱���֮�꣬�ҵ�����Ҳ�ú��ˣ�");
       		command ("say ֻ�����Ѷ��겻������߶�������������ϰ���ˣ��������ٰ���һ��æ��");
       		command ("say �������Ѱ��һ���ˣ�����ʦ�����㣬���˽���Ӧת��Ϊ�������һ���Ի���");
       		command ("say ���������Թ������У���˵��������Ǭ��������������Ǳ���㲻����ȥһ�ԣ�");
       		me->set_temp("jueqing/houyi",1);
       		me->set("jueqing/binghun",1);
       		call_out("destroy", 2, ob);
       		return 1;
       	}
       	return 0;
}
void destroy(object ob)
{
        destruct(ob);
        return;
   }
   
string ask_jueqing()
{
	object book;
	object me=this_player();
	if( me->query("betray/count") )
		return ("�����Ķ����޷�����¹���ѧ��\n");
	if(me->query("family/family_name") != "�¹�" )
                return ("�㲻�����¹�����!!\n");
        if( (string)me->query("gender") !="Ů��")
                return ("���Ϊ����֮��,����֪��Ů���ҵ���˼??\n");
        if(me->query("jueqing_cant"))
      		return ("���������Ե��");
        if( me->query("jueqing_known") > 1 )
      		return ("����Ŀھ��㶼�Ѿ�֪���˰���");
      	if( !me->query("jueqing_known") )
      	{
	      	if( !me->query("jueqing/chimeng"))
	      		return ("����ȥ�ҳ���ʦ��ɣ�");
	      	//if( !me->query("jueqing/zhinu"))
	      	//	return ("����ȥ��֯Ůʦ��ɣ�");
	      	if( !me->query("jueqing/baihua"))
	      		return ("����ȥ�Ұٻ�ʦ��ɣ�");
	      	if( !me->query("jueqing/xiwangmu"))
	      		return ("����ȥ����ʦ���ɣ�");
	      	if( present("duanchang book",me) )
	      		return ("�鶼�õ��ˣ������ú��ж�(read book)����");
	      	command("sigh");
		command("say �ѵ���������ģ��Ҿʹ��������ʽ�Ŀھ��������ܲ�������Ҫ����Ļ�Ե��");
		//command("say ��ʵ�Ҵ���û����ϰ��������ʽ��ֻ�ǰٰ�����֮��ÿ��������¼�ڱ���֮�ϣ�����ȥ�Լ��ж�һ�°ɣ�");
		book = new("/d/moon/obj/duanchang.c");
		if( objectp(book) )
			book->move(me);
		else
			tell_object(me,"��ѽ���ϳ��������ˣ���ȥ����ʦ��\n");
		message_vision("\n�϶�ݸ�$Nһ�����顣\n",me);
		return ("��ʵ�Ҵ���û����ϰ��������ʽ��ֻ�ǰٰ�����֮��ÿ��������¼�ڱ���֮�ϣ�����ȥ�Լ��ж�һ�°ɣ�");
	}
	else//�ڶ���
	{
		if( me->query_skill("moonforce",1) < 300 
		    || me->query_skill("moonshentong",1) < 300 
		    || me->query_skill("xuanhu-blade",1) < 300 
		    || me->query_skill("jueqingbian",1) < 300 
		    || me->query_skill("snowsword",1) < 300 
		   )
			return ("����Ϊ��������������ȫ���վ����������");
		if( me->query_temp("jueqing/houyi") == 1 ) return ("�����롢Ǭ����������������ס�ˣ�");
		if( me->query_temp("jueqing/houyi") == 2 ) return ("����ֻ�о���������������ָ������ˣ���ȥ��ʦ����һ���ɣ���Ӧ��֪��һЩ�����");
		if( me->query_temp("jueqing/sun") == 1 ) return ("����ȥ�Һ���ɣ�");
		if( me->query_temp("jueqing/sun") == 2 ) return ("̫лл���ˣ����鷳�������ǰ���¹��������");
		if( me->query("jueqing/binghun") && !me->query("jueqing/houyi") )
		{
			command ("say лл������õ��˱��꣡");
       			command ("say ֻ�����Ѷ��겻������߶�������������ϰ���ˣ��������ٰ���һ��æ��");
       			command ("say �������Ѱ��һ���ˣ�����ʦ�����㣬���˽���Ӧת��Ϊ�������һ���Ի���");
       			command ("say ���������Թ������У���˵��������Ǭ��������������Ǳ���㲻����ȥһ�ԣ�");
       			me->set_temp("jueqing/houyi",1);
			return ("�ҵ���ĺ���Ϣ��");
		}
		if( me->query("jueqing/houyi") )
		{
			me->set_temp("jueqing/sun",1);
			return ("������ཫ���͵�����֮�ϣ���̫�������ʹ������յ�����ɣ�");
		}
		if( !me->query_temp("jueqing/binghun") )
		{
			command("say ������Ծ������������һ������Ȼ��ˣ��Ҿʹ���������ʽ�����򷽷���");
			command("sigh");
			command("say �뵱������̫����ս�ھ���֮�ϣ���������������Ҳ�ա�");
			me->set_temp("jueqing/binghun",1);
			return ("����ȥ�Ұٻ�ʦ�㣬ѯ�ʹ���ħ��֮�£�");
		}
		else
		{
			return ("�Ͻ�����ɣ�����һ��С��Ϊ�ϣ�");
		}
	}
}