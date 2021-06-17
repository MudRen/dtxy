// gao.c

inherit NPC;
int zhuyao();

void create()
{
       set_name("��Ա��", ({"gao yuanwai", "gao"}));

set("long","�߼�ׯ�����ˣ��Ե��ֺ����ģ�\n��˵�����Ӧ���ֺǺǵأ���ȴ��ü����������������ʲô���£�\n");
       set("gender", "����");
       set("age", 46);
       set("title", "ׯ��");
       set("attitude", "peaceful");
       set("shen_type", 1);
	set("combat_exp", 5000);
        set_skill("unarmed", 15);
	set_skill("dodge", 30);
	set_skill("parry", 15);
set("inquiry", ([
"name": "�Ϸ��ոߣ����Ǽ��е����ˣ�\n",
"here": "����ׯ��Ҳ��\n",
"����": (: zhuyao :),
]) );

	setup();
       add_money("silver", 3+random(5));
	carry_object("/d/ourhome/obj/choupao")->wear();
}
int accept_object(object who,object ob)
{
        object m;
        if (ob->query("id")=="mmmmmm") {
                say("��ׯ��Ц������л"  + RANK_D->query_respect(who) +
"���Ϸ����������ˣ�\n��ׯ��˵����������ǰһ����ʿ���µģ�Ҳ��������ã�\n");
	m=new("/d/gao/obj/pa_book");
        m->move(who);
	call_out("destroy", 1, ob);
	return 1;
        }
	else return 0;
}
void destroy(object ob)
{
        destruct(ob);
        return;
}

int zhuyao()
{
 object me=this_player();
 object obp;
 if (me->query("obstacle/gao")=="done")
 {
 	message_vision("Ц������л��Ϊ����Ϊ�Ҷ�������\n��ׯ��˵����������ǰһ����ʿ���µģ�Ҳ��������ã�\n",me);
 	obp=new("/d/gao/obj/pa_book");
 	obp->move(me);
 	obp=new("/d/gao/obj/pa");
 	obp->move(me);
 }
 else
 {
 	say("��ׯ��һ�����ݣ�˵����ǰ�������˸�������ӲҪ����Ů��Ϊ�ޡ�\n");
 	say("�������������������Ů���ͱ����ں�Ժ�����¥�\n");
 	me->set_temp("obstacle/yuanwai",1);
 	message_vision("$N˵���п���������\n",this_object());
 }
 return 1;
}


void announce_success (object who)
{
  int i;
  object ob;
  if (who->query("combat_exp") < 10000)
    return;
  if (who->query("obstacle/gao") == "done")
    return;

  i = random(600);
  who->add("obstacle/number",1);
  who->set("obstacle/gao","done");
//  ob=new("/clone/jian");
//  ob->move(who);
//  who->add("combat_exp",i+4000);
  who->add("daoxing",i+4000);
  command("chat "+who->query("name")+"����ׯ������˽�");
  command("chat "+who->query("name")+"˳������������һ�أ�");
  tell_object (who,"��Ӯ����"+chinese_number(4)+"��"+
               chinese_number(i/4)+"��"+
               chinese_number((i-(i/4)*4)*3)+"ʱ���ĵ��У�\n");
  who->save();
}
