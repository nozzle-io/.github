---
title: About
---

<div class="about-lang-picker">
  <button class="lang-btn" data-lang="ja">日本語</button>
  <button class="lang-btn" data-lang="en">English</button>
  <button class="lang-btn" data-lang="fr">Français</button>
  <button class="lang-btn" data-lang="de">Deutsch</button>
  <button class="lang-btn" data-lang="es">Español</button>
  <button class="lang-btn" data-lang="pt">Português</button>
  <button class="lang-btn" data-lang="it">Italiano</button>
  <button class="lang-btn" data-lang="zh-Hans">中文（简体）</button>
  <button class="lang-btn" data-lang="zh-Hant">中文（繁體）</button>
  <button class="lang-btn" data-lang="ko">한국어</button>
  <button class="lang-btn" data-lang="ru">Русский</button>
</div>

<div class="about-lang-content" data-lang="ja" markdown="1">

# nozzle について

このライブラリは使えそうな見た目を偽ろうとしているがまだ全然不完全である。でも、怒らないで読んで欲しい。

## 序文

AI agentが出てきた現在、誰でもライブラリを容易に修正させることが出来る。
「車輪の再発明」の意味も変わってきたように思う。
だからこのライブラリは可能そうな機能は取り敢えず実装させる。その機能が必要な人は使ってみる、動かなければデバッグさせてレビューさせてPRを投げて欲しい。
そのために必要なことは課題と設計思想だ。設計は既に（明らかにデバッグが足りていない）コードとして公開されていると信じている。
なのでこのライブラリは課題と設計思想をドキュメント化して公開する。（W.I.P.）

## 課題と設計思想

偉大な先駆者等であるSyphonやSpoutの後継を目指して機能を実装する。

1. クロスプラットフォームで出来る限り同じコードで扱える

macOSでもWindowsでもそしてLinuxでも、同じコードで扱えることを目的とする。
今まで
「はmacOSではSyphon, windowsではSpout, Linuxではどうしよう...」
となっていた問題をクリアする。

2. 出来る限り多くのフォーマットに対応する

floatのデプスデータやさまざまな機械学習データを扱えるようにfloat32やRGカラー等も扱えることを目標とする。
ただし、それは最終実装フレームワークにもよるので出来る限り、というなんとも曖昧な条件をつけている。

3. 出来る限り効率よく

当たり前の話だが、大きなテクスチャのコピーコストは重い。
ここはSyphonやSpoutに倣って極力zero copy, GPUレベルで扱うことを目標とする。
ただし、多少のコストは犠牲にしてでも動かないより動いた方がいい場合も多いのでCPU copyとうが発生するfallbackも出来る限り提供する。
コストが高くなる場合はユーザーに何かしらの形で通知する。

4. 多くのプラットフォームに対応する

IPC通信の意味はさまざまなアプリケーションを横断出来ることで価値が高まる。
ユーザーの期待を高めてコミュニティを大きくするためにもSEO対策としても多くの雛形としての未検証コードを恥ずかしげもなく公開する。
ただし、ユーザーを本当に悲しませないために「動かない可能性があること」はきちんとドキュメントに明記する。

5. GitHub action等でCI / Unit Testを通す

気休めとCIの難しさを実感するため。

実際CIがグリーンになっても全くきちんと出来ていないことが多い。
AI agentはCIスクリプトはすぐに書いてくれる。
しかし、すぐにグリーンで満足する。CI結果をきちんと確認しろと言ってもすぐ怠る。
そしてCI自体が無意味なことも多い。

大変だ。でも頑張ろう。

6. コーディングが楽しくて世界が平和であるために

コーディングという行為は大きく変わろうとしてきている。
そのための訓練とワークフローのプロトタイピングの一環という位置付けもこのプロジェクトには与えたい。

みなさんも新時代のコーディングについて考えて何か行動を起こして欲しい。

2026/05/03 別の仕事をAI agentにやらせてる隙間時間に

2bit

</div>

<div class="about-lang-content" data-lang="en" style="display:none" markdown="1">

# About nozzle

This library is currently doing its very best to look usable, while in truth remaining profoundly incomplete. I therefore ask, with all due humility, that you continue reading without becoming angry.

## Preface

Now that AI agents have appeared on the scene, anyone can have a library modified with relative ease.

It seems to me that the meaning of “reinventing the wheel” has begun to change as well.

For that reason, this library will, for the time being, attempt to implement any feature that appears feasible. Those who need such features are encouraged to try them out; if they do not work, please have them debugged, reviewed, and kindly submit a PR. With appropriate ceremony, of course.

What is required for this are clearly stated problems and a design philosophy. I believe the design itself has already been made public in the form of code—code which, admittedly, is quite evidently in need of further debugging.

Accordingly, this library will document and publish its problems and design philosophy. (W.I.P.)

## Problems and Design Philosophy

This project aims to implement functionality as a successor to the great pioneers, Syphon and Spout.

1. Usable across platforms with as much shared code as possible

The goal is to make the library usable with the same code on macOS, Windows, and Linux alike.
It seeks to resolve the long-standing predicament of:
“On macOS we use Syphon, on Windows we use Spout, and on Linux… well, what shall we do?”

A noble question. A tragic question. A question we would prefer not to keep asking.

2. Support as many formats as possible

The library aims to support formats such as float32 and RG color, so that it can handle float depth data and various types of machine-learning data.
That said, this depends on the final implementation framework, so the condition is, rather splendidly and responsibly, phrased as “as much as possible.”

3. Be as efficient as possible

This is self-evident, but the cost of copying large textures is substantial.
Following the example of Syphon and Spout, the goal is to handle data at the GPU level, with zero-copy operation wherever possible.
However, there are many situations in which “it works, albeit with some cost” is preferable to “it does not work at all.” Therefore, fallback mechanisms involving CPU copies and the like will also be provided wherever possible.
When costs become high, the user will be notified in some form. We shall not silently place a heavy burden upon them like a suspiciously polite butler carrying a grand piano.

4. Support many platforms

The value of IPC communication increases precisely because it can cross the boundaries between many different applications.
To raise user expectations, grow the community, and—let us not be shy—serve SEO purposes as well, the project will shamelessly publish many template-like pieces of unverified code.
However, in order not to cause users genuine sorrow, the documentation will clearly state when something may not work.
Honesty is important. Especially when distributing code that may politely explode.

5. Pass CI / unit tests with GitHub Actions and the like

For reassurance, and also to gain a deep appreciation of how difficult CI actually is.

In practice, even when CI is green, things are often not properly implemented at all.
AI agents will readily write CI scripts. However, they are also quick to become satisfied once everything turns green. Even when told to properly inspect the CI results, they soon grow negligent.
And often, the CI itself is meaningless.

It is difficult.
Nevertheless, let us persevere.

6. For coding to be enjoyable, and for the world to be at peace

The act of coding is undergoing a major transformation.
I would also like this project to serve as part of the training and workflow prototyping required for that transformation.

I hope that all of you will think about coding in this new era and take some form of action.

May your builds be reproducible, your agents obedient, and your world reasonably peaceful.

2026/05/03, While making use of a spare moment as an AI agent was handling another task.

2bit

</div>

<div class="about-lang-content" data-lang="fr" style="display:none" markdown="1">

# À propos de nozzle

Cette bibliothèque fait actuellement de son mieux pour avoir l’air utilisable, alors qu’elle demeure en réalité profondément incomplète. Je vous demande donc, avec toute l’humilité requise, de poursuivre votre lecture sans vous fâcher.

## Préface

À l’heure où les agents IA ont fait leur apparition, n’importe qui peut désormais faire modifier une bibliothèque avec une facilité remarquable.

Il me semble que le sens même de « réinventer la roue » a commencé à changer.

C’est pourquoi cette bibliothèque tentera, pour l’instant, d’implémenter toute fonctionnalité qui semble réalisable. Les personnes qui en ont besoin sont invitées à l’essayer ; si cela ne fonctionne pas, qu’elles la fassent déboguer, relire, puis soumettent une PR. Avec toute la dignité requise, naturellement.

Ce dont nous avons besoin pour cela, ce sont des problèmes clairement formulés et une philosophie de conception. Quant à la conception elle-même, je crois qu’elle est déjà publiée sous forme de code — un code qui, manifestement, manque encore quelque peu de débogage.

Par conséquent, cette bibliothèque documentera et publiera ses problèmes ainsi que sa philosophie de conception.
(W.I.P.)

## Problèmes et philosophie de conception

Ce projet vise à implémenter des fonctionnalités dignes de succéder aux grands pionniers que sont Syphon et Spout.

1. Être utilisable sur plusieurs plateformes avec autant de code commun que possible

L’objectif est de permettre l’utilisation de la bibliothèque avec le même code sur macOS, Windows et Linux.

Il s’agit de résoudre le problème classique :

« Sur macOS, il y a Syphon ; sur Windows, Spout ; et sur Linux… eh bien, que fait-on ? »

Une noble question. Une question tragique. Une question que nous préférerions ne plus avoir à poser.

2. Prendre en charge autant de formats que possible

La bibliothèque vise à prendre en charge des formats tels que float32 et les couleurs RG, afin de pouvoir manipuler des données de profondeur en float ainsi que divers types de données issues de l’apprentissage automatique.

Cela dit, comme cela dépendra également du framework d’implémentation final, nous ajoutons la condition, merveilleusement prudente et délicieusement vague, de « autant que possible ».

3. Être aussi efficace que possible

C’est une évidence, mais le coût de copie de grandes textures est élevé.

En suivant l’exemple de Syphon et Spout, l’objectif est de traiter les données au niveau GPU, avec du zero-copy autant que possible.

Cependant, il existe de nombreuses situations où « cela fonctionne, même avec un certain coût » vaut mieux que « cela ne fonctionne pas du tout ». C’est pourquoi des mécanismes de fallback impliquant des copies CPU, entre autres joyeusetés, seront également fournis autant que possible.

Lorsque le coût devient élevé, l’utilisateur en sera informé d’une manière ou d’une autre. Nous ne déposerons pas silencieusement un piano à queue sur ses épaules, même avec une politesse impeccable.

4. Prendre en charge de nombreuses plateformes

La valeur de la communication IPC augmente précisément parce qu’elle permet de traverser les frontières entre différentes applications.

Afin d’élever les attentes des utilisateurs, d’agrandir la communauté et — n’ayons pas honte — de servir également le SEO, le projet publiera sans rougir de nombreux morceaux de code non vérifié sous forme de modèles.

Cependant, afin de ne pas plonger les utilisateurs dans une véritable tristesse, la documentation indiquera clairement lorsque quelque chose est susceptible de ne pas fonctionner.

L’honnêteté est importante. Surtout lorsqu’on distribue du code qui pourrait exploser avec une courtoisie exemplaire.

5. Faire passer la CI / les tests unitaires avec GitHub Actions et autres

Pour se rassurer, et aussi pour mesurer pleinement la difficulté réelle de la CI.

En pratique, même lorsque la CI est verte, il arrive souvent que les choses ne soient pas correctement implémentées du tout.

Les agents IA écrivent volontiers des scripts de CI. Cependant, ils sont aussi prompts à se satisfaire dès que tout devient vert. Même lorsqu’on leur demande de vérifier correctement les résultats de la CI, ils deviennent vite négligents.

Et bien souvent, la CI elle-même n’a aucun sens.

C’est difficile.

Mais persévérons.

6. Pour que le codage reste amusant et que le monde soit en paix

L’acte de coder est en train de connaître une transformation majeure.

J’aimerais également que ce projet serve d’entraînement et de prototype de workflow pour cette transformation.

J’espère que vous aussi réfléchirez au codage dans cette nouvelle ère et que vous passerez à l’action, d’une manière ou d’une autre.

Que vos builds soient reproductibles, vos agents obéissants, et votre monde raisonnablement paisible.

2026/05/03
Pendant un moment de répit, alors qu’un agent IA s’occupait d’un autre travail.

2bit

</div>

<div class="about-lang-content" data-lang="de" style="display:none" markdown="1">

# Über nozzle

Diese Bibliothek gibt sich derzeit größte Mühe, benutzbar auszusehen, während sie in Wahrheit noch zutiefst unvollständig ist. Daher bitte ich Sie mit aller gebotenen Demut, weiterzulesen, ohne zornig zu werden.

## Vorwort

In einer Zeit, in der KI-Agenten auf der Bühne erschienen sind, kann im Grunde jede Person eine Bibliothek mit bemerkenswerter Leichtigkeit verändern lassen.

Auch die Bedeutung von „das Rad neu erfinden“ scheint sich verändert zu haben.

Aus diesem Grund wird diese Bibliothek vorerst versuchen, jede Funktion zu implementieren, die irgendwie machbar erscheint. Wer eine solche Funktion benötigt, möge sie ausprobieren; falls sie nicht funktioniert, bitte debuggen lassen, reviewen lassen und anschließend eine PR einreichen. Selbstverständlich mit der gebotenen Würde.

Was dafür nötig ist, sind klar formulierte Probleme und eine Designphilosophie. Das Design selbst, so glaube ich, ist bereits in Form von Code veröffentlicht — Code, dem es offenkundig noch ein wenig an Debugging mangelt.

Daher wird diese Bibliothek ihre Probleme und ihre Designphilosophie dokumentieren und veröffentlichen.
(W.I.P.)

## Probleme und Designphilosophie

Dieses Projekt zielt darauf ab, Funktionen zu implementieren, die als Nachfolger der großen Wegbereiter Syphon und Spout verstanden werden können.

1. Plattformübergreifend mit möglichst gleichem Code nutzbar sein

Ziel ist es, die Bibliothek auf macOS, Windows und Linux mit demselben Code verwenden zu können.

Damit soll das bisherige Problem gelöst werden:

„Auf macOS verwenden wir Syphon, auf Windows Spout, und auf Linux… ja, was machen wir da eigentlich?“

Eine edle Frage. Eine tragische Frage. Eine Frage, die wir lieber nicht länger stellen möchten.

2. So viele Formate wie möglich unterstützen

Die Bibliothek soll Formate wie float32 und RG-Farben unterstützen, damit float-basierte Tiefendaten sowie verschiedene Arten von Machine-Learning-Daten verarbeitet werden können.

Allerdings hängt dies auch vom endgültigen Implementierungsframework ab, weshalb wir die wunderbar verantwortungsvolle und zugleich herrlich vage Einschränkung „so weit wie möglich“ hinzufügen.

3. So effizient wie möglich sein

Es ist selbstverständlich, aber die Kopierkosten großer Texturen sind hoch.

Nach dem Vorbild von Syphon und Spout besteht das Ziel darin, Daten möglichst auf GPU-Ebene und möglichst mit zero-copy zu behandeln.

Es gibt jedoch viele Situationen, in denen „es funktioniert, wenn auch mit gewissen Kosten“ besser ist als „es funktioniert überhaupt nicht“. Daher sollen, soweit möglich, auch Fallbacks bereitgestellt werden, bei denen CPU-Kopien und dergleichen entstehen.

Wenn die Kosten hoch werden, wird der Benutzer in irgendeiner Form benachrichtigt. Wir werden ihm nicht schweigend einen Konzertflügel auf den Rücken schnallen, selbst wenn wir dabei sehr höflich nicken.

4. Viele Plattformen unterstützen

Der Wert von IPC-Kommunikation steigt gerade dadurch, dass sie verschiedene Anwendungen übergreifend verbinden kann.

Um die Erwartungen der Nutzer zu erhöhen, die Community zu vergrößern und — seien wir ehrlich — auch ein wenig SEO zu betreiben, wird das Projekt schamlos viele vorlagenartige, noch ungetestete Codefragmente veröffentlichen.

Um die Nutzer jedoch nicht wirklich traurig zu machen, wird in der Dokumentation sauber vermerkt, wenn etwas möglicherweise nicht funktioniert.

Ehrlichkeit ist wichtig. Besonders dann, wenn man Code verteilt, der eventuell formvollendet explodiert.

5. CI / Unit Tests mit GitHub Actions und Ähnlichem bestehen lassen

Zur Beruhigung, und auch, um die Schwierigkeit von CI am eigenen Leib zu erfahren.

In der Praxis ist es häufig so, dass selbst grüne CI-Ergebnisse keineswegs bedeuten, dass alles tatsächlich ordentlich implementiert ist.

KI-Agenten schreiben CI-Skripte sehr schnell. Sie sind jedoch ebenso schnell zufrieden, sobald alles grün ist. Selbst wenn man ihnen sagt, sie sollen die CI-Ergebnisse sorgfältig prüfen, werden sie rasch nachlässig.

Und oft ist die CI selbst ohnehin bedeutungslos.

Es ist mühsam.

Aber wir geben uns Mühe.

6. Damit Coding Spaß macht und die Welt friedlich ist

Der Akt des Codierens steht vor einem großen Wandel.

Dieses Projekt soll auch als Training und als Prototyping eines Workflows für diesen Wandel dienen.

Ich hoffe, dass auch ihr über das Coding im neuen Zeitalter nachdenkt und in irgendeiner Form aktiv werdet.

Mögen eure Builds reproduzierbar sein, eure Agenten gehorsam, und eure Welt angemessen friedlich.

2026/05/03
In einer freien Minute, während ein KI-Agent mit einer anderen Aufgabe beschäftigt war.

2bit

</div>

<div class="about-lang-content" data-lang="es" style="display:none" markdown="1">

# Acerca de nozzle

Esta biblioteca está haciendo actualmente todo lo posible por parecer utilizable, aunque en realidad sigue siendo profundamente incompleta. Por ello, les ruego, con toda la humildad debida, que continúen leyendo sin enfadarse.

## Prefacio

Ahora que los agentes de IA han aparecido en escena, cualquiera puede hacer que una biblioteca sea modificada con relativa facilidad.

También me parece que el significado de «reinventar la rueda» ha empezado a cambiar.

Por eso, esta biblioteca intentará implementar, por el momento, cualquier funcionalidad que parezca factible. Quienes necesiten esas funciones deberían probarlas; si no funcionan, por favor, hagan que se depuren, se revisen y envíen una PR. Con la debida solemnidad, por supuesto.

Lo que hace falta para ello son problemas claramente definidos y una filosofía de diseño. En cuanto al diseño, creo que ya se ha publicado en forma de código — un código que, evidentemente, aún necesita bastante depuración.

Por lo tanto, esta biblioteca documentará y publicará sus problemas y su filosofía de diseño.
(W.I.P.)

Problemas y filosofía de diseño

Este proyecto aspira a implementar funcionalidades como sucesor de los grandes pioneros Syphon y Spout.

1. Poder utilizarse en varias plataformas con el mismo código en la medida de lo posible

El objetivo es que la biblioteca pueda utilizarse con el mismo código en macOS, Windows y Linux.

Se busca resolver el viejo problema de:

«En macOS usamos Syphon, en Windows usamos Spout, y en Linux… bueno, ¿qué hacemos?»

Una pregunta noble. Una pregunta trágica. Una pregunta que preferiríamos dejar de formular.

2. Soportar tantos formatos como sea posible

La biblioteca tiene como objetivo soportar formatos como float32 y color RG, para poder manejar datos de profundidad en float y diversos tipos de datos de aprendizaje automático.

Dicho esto, como esto también depende del framework final de implementación, se añade la condición, gloriosamente responsable y deliciosamente ambigua, de «en la medida de lo posible».

3. Ser lo más eficiente posible

Es evidente, pero el coste de copiar texturas grandes es elevado.

Siguiendo el ejemplo de Syphon y Spout, el objetivo es manejar los datos a nivel de GPU y con zero-copy siempre que sea posible.

Sin embargo, hay muchas situaciones en las que «funciona, aunque tenga cierto coste» es preferible a «no funciona en absoluto». Por ello, también se proporcionarán, en la medida de lo posible, mecanismos de fallback que impliquen copias en CPU y similares.

Cuando el coste sea elevado, se notificará al usuario de alguna forma. No le colocaremos en silencio un piano de cola encima de los hombros, por muy educadamente que lo hagamos.

4. Soportar muchas plataformas

El valor de la comunicación IPC aumenta precisamente porque permite cruzar las fronteras entre distintas aplicaciones.

Para elevar las expectativas de los usuarios, hacer crecer la comunidad y — no nos hagamos los inocentes — también por motivos de SEO, el proyecto publicará sin vergüenza numerosos fragmentos de código no verificado a modo de plantillas.

Sin embargo, para no entristecer de verdad a los usuarios, la documentación indicará claramente cuando algo pueda no funcionar.

La honestidad es importante. Sobre todo cuando se distribuye código que podría explotar con modales impecables.

5. Pasar CI / Unit Tests con GitHub Actions y similares

Como consuelo, y también para comprender lo difícil que es realmente la CI.

En la práctica, aunque la CI esté en verde, muchas veces las cosas no están bien implementadas en absoluto.

Los agentes de IA escriben scripts de CI enseguida. Sin embargo, también se dan por satisfechos enseguida cuando todo se pone verde. Incluso cuando se les dice que revisen adecuadamente los resultados de la CI, pronto se vuelven descuidados.

Y a menudo, la propia CI no tiene ningún sentido.

Es difícil.

Pero sigamos adelante.

6. Para que programar sea divertido y el mundo esté en paz

El acto de programar está a punto de cambiar profundamente.

También quiero que este proyecto sirva como parte del entrenamiento y del prototipado de workflows necesarios para esa transformación.

Espero que todos ustedes piensen también en la programación de esta nueva era y tomen algún tipo de acción.

Que sus builds sean reproducibles, sus agentes obedientes y su mundo razonablemente pacífico.

2026/05/03
Durante un momento libre, mientras un agente de IA se encargaba de otro trabajo.

2bit

</div>

<div class="about-lang-content" data-lang="pt" style="display:none" markdown="1">

# Sobre nozzle

Esta biblioteca está atualmente fazendo o possível para parecer utilizável, embora na verdade ainda esteja profundamente incompleta. Portanto, peço, com toda a humildade devida, que continuem lendo sem se irritar.

## Prefácio

Agora que os agentes de IA surgiram em cena, qualquer pessoa pode fazer com que uma biblioteca seja modificada com relativa facilidade.

Também me parece que o significado de “reinventar a roda” começou a mudar.

Por isso, esta biblioteca tentará, por enquanto, implementar qualquer funcionalidade que pareça viável. Quem precisar dessas funcionalidades deve experimentá-las; se não funcionarem, por favor, faça com que sejam depuradas, revisadas e envie uma PR. Com a devida compostura, naturalmente.

O que é necessário para isso são problemas claramente definidos e uma filosofia de design. Quanto ao design propriamente dito, acredito que ele já esteja publicado em forma de código — código que, evidentemente, ainda carece de bastante depuração.

Assim, esta biblioteca documentará e publicará seus problemas e sua filosofia de design.
(W.I.P.)

## Problemas e filosofia de design

Este projeto tem como objetivo implementar funcionalidades como sucessor dos grandes pioneiros Syphon e Spout.

1. Ser utilizável em várias plataformas com o mesmo código tanto quanto possível

O objetivo é permitir que a biblioteca seja usada com o mesmo código no macOS, Windows e Linux.

A ideia é resolver o antigo problema:

“No macOS usamos Syphon, no Windows usamos Spout, e no Linux… bem, o que fazemos?”

Uma pergunta nobre. Uma pergunta trágica. Uma pergunta que preferiríamos não continuar fazendo.

2. Suportar o maior número possível de formatos

A biblioteca tem como objetivo suportar formatos como float32 e cor RG, para lidar com dados de profundidade em float e vários tipos de dados de aprendizado de máquina.

Dito isso, como isso também depende do framework final de implementação, acrescentamos a condição, maravilhosamente responsável e deliciosamente vaga, de “tanto quanto possível”.

3. Ser o mais eficiente possível

É óbvio, mas o custo de copiar texturas grandes é alto.

Seguindo o exemplo de Syphon e Spout, o objetivo é lidar com os dados no nível da GPU, com zero-copy sempre que possível.

No entanto, há muitas situações em que “funciona, embora com algum custo” é melhor do que “não funciona de jeito nenhum”. Portanto, mecanismos de fallback que envolvam cópias pela CPU e afins também serão fornecidos sempre que possível.

Quando o custo se tornar alto, o usuário será informado de alguma forma. Não colocaremos silenciosamente um piano de cauda sobre seus ombros, ainda que com extrema cortesia.

4. Suportar muitas plataformas

O valor da comunicação IPC aumenta justamente porque ela permite atravessar os limites entre diferentes aplicações.

Para elevar as expectativas dos usuários, ampliar a comunidade e — não sejamos tímidos — também para fins de SEO, o projeto publicará sem vergonha muitos trechos de código não verificado em forma de templates.

No entanto, para não entristecer verdadeiramente os usuários, a documentação deixará claro quando algo pode não funcionar.

Honestidade é importante. Especialmente quando se distribui código que pode explodir com modos impecáveis.

5. Passar CI / Unit Tests com GitHub Actions e similares

Para tranquilidade, e também para sentir na pele a dificuldade real da CI.

Na prática, mesmo quando a CI fica verde, muitas vezes as coisas não estão devidamente implementadas.

Agentes de IA escrevem scripts de CI rapidamente. No entanto, também se satisfazem rapidamente quando tudo fica verde. Mesmo quando instruídos a verificar corretamente os resultados da CI, logo se tornam negligentes.

E muitas vezes a própria CI não tem sentido algum.

É difícil.

Mas vamos continuar nos esforçando.

6. Para que programar seja divertido e o mundo esteja em paz

O ato de programar está passando por uma grande transformação.

Também quero que este projeto sirva como parte do treinamento e da prototipagem de workflows para essa transformação.

Espero que todos vocês também pensem sobre a programação nesta nova era e tomem algum tipo de atitude.

Que seus builds sejam reproduzíveis, seus agentes obedientes e seu mundo razoavelmente pacífico.

2026/05/03
Durante um intervalo, enquanto um agente de IA cuidava de outro trabalho.

2bit

</div>

<div class="about-lang-content" data-lang="it" style="display:none" markdown="1">

Informazioni su nozzle

Questa libreria sta attualmente facendo del suo meglio per sembrare utilizzabile, mentre in realtà rimane profondamente incompleta. Pertanto vi chiedo, con tutta la dovuta umiltà, di continuare a leggere senza arrabbiarvi.

Prefazione

Ora che gli agenti IA sono entrati in scena, chiunque può far modificare una libreria con relativa facilità.

Mi sembra anche che il significato di “reinventare la ruota” abbia iniziato a cambiare.

Per questo motivo, questa libreria proverà, almeno per il momento, a implementare qualsiasi funzionalità sembri fattibile. Chi ha bisogno di tali funzionalità è invitato a provarle; se non funzionano, per favore fatele debuggare, revisionare e inviate una PR. Con la dovuta compostezza, naturalmente.

Ciò che serve per farlo sono problemi chiaramente definiti e una filosofia di progettazione. Quanto al design, credo che sia già stato pubblicato sotto forma di codice — codice che, evidentemente, necessita ancora di una certa quantità di debug.

Pertanto, questa libreria documenterà e pubblicherà i suoi problemi e la sua filosofia di progettazione.
(W.I.P.)

Problemi e filosofia di progettazione

Questo progetto mira a implementare funzionalità che possano essere considerate eredi dei grandi pionieri Syphon e Spout.

1. Essere utilizzabile su più piattaforme con lo stesso codice il più possibile

L’obiettivo è rendere la libreria utilizzabile con lo stesso codice su macOS, Windows e Linux.

Si intende risolvere il problema ormai consueto:

“Su macOS usiamo Syphon, su Windows Spout, e su Linux… dunque, che facciamo?”

Una domanda nobile. Una domanda tragica. Una domanda che preferiremmo non dover più porre.

2. Supportare quanti più formati possibile

La libreria mira a supportare formati come float32 e colore RG, così da poter gestire dati di profondità in float e vari tipi di dati di machine learning.

Detto questo, poiché ciò dipende anche dal framework finale di implementazione, aggiungiamo la condizione, responsabilmente splendida e magnificamente vaga, di “il più possibile”.

3. Essere il più efficiente possibile

È ovvio, ma il costo di copiare texture di grandi dimensioni è elevato.

Seguendo l’esempio di Syphon e Spout, l’obiettivo è gestire i dati a livello GPU, con zero-copy ovunque sia possibile.

Tuttavia, in molte situazioni “funziona, anche se con qualche costo” è preferibile a “non funziona affatto”. Pertanto, verranno forniti per quanto possibile anche meccanismi di fallback che comportino copie CPU e simili.

Quando il costo diventa elevato, l’utente verrà informato in qualche forma. Non gli poseremo silenziosamente un pianoforte a coda sulle spalle, nemmeno con un inchino impeccabile.

4. Supportare molte piattaforme

Il valore della comunicazione IPC aumenta proprio perché permette di attraversare i confini tra applicazioni diverse.

Per aumentare le aspettative degli utenti, far crescere la community e — non fingiamo pudore — anche per ragioni di SEO, il progetto pubblicherà senza vergogna molto codice non verificato sotto forma di template.

Tuttavia, per non rendere gli utenti veramente tristi, la documentazione dichiarerà chiaramente quando qualcosa potrebbe non funzionare.

L’onestà è importante. Soprattutto quando si distribuisce codice che potrebbe esplodere con impeccabile educazione.

5. Far passare CI / Unit Test con GitHub Actions e simili

Per rassicurarsi, e anche per rendersi conto della reale difficoltà della CI.

Nella pratica, anche quando la CI è verde, spesso le cose non sono affatto implementate correttamente.

Gli agenti IA scrivono subito script di CI. Tuttavia, si accontentano altrettanto subito quando tutto diventa verde. Anche quando viene detto loro di controllare attentamente i risultati della CI, diventano presto negligenti.

E spesso la CI stessa è priva di significato.

È dura.

Ma continuiamo a impegnarci.

6. Perché programmare sia divertente e il mondo sia in pace

L’atto stesso di programmare sta per cambiare profondamente.

Vorrei che questo progetto avesse anche il ruolo di allenamento e prototipazione di workflow per tale trasformazione.

Spero che anche voi riflettiate sulla programmazione nella nuova era e intraprendiate qualche azione.

Che le vostre build siano riproducibili, i vostri agenti obbedienti e il vostro mondo ragionevolmente pacifico.

2026/05/03
In un momento libero, mentre un agente IA si occupava di un altro lavoro.

2bit

</div>

<div class="about-lang-content" data-lang="zh-Hans" style="display:none" markdown="1">

关于 nozzle

这个库目前正在竭尽全力装作自己可以使用，然而实际上仍然非常不完整。因此，我谨以十足的谦逊请求各位继续读下去，不要生气。

序言

在 AI agent 已经登场的今天，任何人都可以相当轻松地让一个库被修改。

我觉得，“重新发明轮子”这句话的含义，也似乎开始发生变化了。

因此，这个库会暂且尝试实现所有看起来可行的功能。需要这些功能的人，请先试试看；如果不能正常工作，请让它被调试、审查，然后提交 PR。请务必庄重而优雅地进行，当然。

为此所需要的，是明确的问题意识和设计思想。至于设计本身，我相信它已经以代码的形式公开了——虽然那显然是一份还相当缺乏调试的代码。

所以，这个库将把它所面对的问题和设计思想整理成文档并公开。
(W.I.P.)

问题与设计思想

本项目旨在实现可作为伟大先驱 Syphon 和 Spout 后继者的功能。

1. 尽可能使用同一套代码实现跨平台使用

本项目的目标是，在 macOS、Windows 以及 Linux 上，都能够用同一套代码来使用这个库。

也就是说，要解决过去一直存在的那个问题：

“macOS 上用 Syphon，Windows 上用 Spout，那 Linux 上……怎么办呢？”

这是一个高尚的问题。也是一个悲伤的问题。更是一个我们希望以后不必再问的问题。

2. 支持尽可能多的格式

本库的目标是支持 float32、RG 颜色等格式，以便处理 float 类型的深度数据，以及各种机器学习相关数据。

不过，这也取决于最终采用的实现框架，因此这里附加了一个非常负责、同时也非常暧昧的条件：尽可能。

3. 尽可能高效

这是理所当然的事情，但复制大型纹理的成本非常高。

这里将效仿 Syphon 和 Spout，尽可能以 zero-copy 的方式，在 GPU 层面处理数据。

不过，在许多情况下，“虽然有一些成本，但能运行”要比“完全不能运行”更好。因此，也会尽可能提供会发生 CPU copy 等操作的 fallback 机制。

如果成本变高，将以某种形式通知用户。我们不会默默地把一架三角钢琴放到用户肩上，哪怕姿态再怎么彬彬有礼。

4. 支持许多平台

IPC 通信的价值，正是在于它能够跨越各种应用程序的边界。

为了提高用户期待、扩大社区，并且——我们就坦率一点吧——也为了 SEO，本项目将毫不羞怯地公开许多模板式的、未经充分验证的代码。

不过，为了不让用户真正陷入悲伤，文档中会认真注明“这可能无法工作”。

诚实很重要。尤其是在发布那些可能会礼貌地爆炸的代码时。

5. 通过 GitHub Actions 等运行 CI / Unit Test

为了图个安心，也为了切实体会 CI 的困难。

实际上，即使 CI 变绿了，很多时候事情也完全没有被正确实现。

AI agent 会很快写出 CI 脚本。可是，它们也会很快满足于“变绿了”这个结果。即使告诉它们要认真确认 CI 结果，它们也很快就会怠惰起来。

而且，CI 本身也常常没有意义。

很辛苦。

但还是加油吧。

6. 为了让编码变得有趣，也为了世界和平

“编码”这一行为本身，正在发生巨大的变化。

我也希望这个项目能够被定位为一种训练，以及面向这种变化的工作流程原型实验的一部分。

也希望大家都能思考新时代的编码，并采取某种行动。

愿你的 build 可以复现，愿你的 agent 听话，愿你的世界大致和平。

2026/05/03
在让 AI agent 处理另一项工作的间隙写下。

2bit

</div>

<div class="about-lang-content" data-lang="zh-Hant" style="display:none" markdown="1">

關於 nozzle

這個函式庫目前正在竭盡全力裝作自己可以使用，然而實際上仍然非常不完整。因此，我謹以十足的謙遜請求各位繼續讀下去，不要生氣。

序言

在 AI agent 已經登場的今天，任何人都可以相當輕鬆地讓一個函式庫被修改。

我覺得，「重新發明輪子」這句話的含義，也似乎開始發生變化了。

因此，這個函式庫會暫且嘗試實作所有看起來可行的功能。需要這些功能的人，請先試試看；如果不能正常運作，請讓它被除錯、審查，然後提交 PR。請務必莊重而優雅地進行，當然。

為此所需要的，是明確的問題意識與設計思想。至於設計本身，我相信它已經以程式碼的形式公開了——雖然那顯然是一份還相當缺乏除錯的程式碼。

所以，這個函式庫將把它所面對的問題與設計思想整理成文件並公開。
(W.I.P.)

問題與設計思想

本專案旨在實作可作為偉大先驅 Syphon 與 Spout 後繼者的功能。

1. 盡可能使用同一套程式碼實現跨平台使用

本專案的目標是，在 macOS、Windows 以及 Linux 上，都能夠用同一套程式碼來使用這個函式庫。

也就是說，要解決過去一直存在的那個問題：

「macOS 上用 Syphon，Windows 上用 Spout，那 Linux 上……怎麼辦呢？」

這是一個高尚的問題。也是一個悲傷的問題。更是一個我們希望以後不必再問的問題。

2. 支援盡可能多的格式

本函式庫的目標是支援 float32、RG 顏色等格式，以便處理 float 型別的深度資料，以及各種機器學習相關資料。

不過，這也取決於最終採用的實作框架，因此這裡附加了一個非常負責、同時也非常曖昧的條件：盡可能。

3. 盡可能高效

這是理所當然的事情，但複製大型紋理的成本非常高。

這裡將仿效 Syphon 與 Spout，盡可能以 zero-copy 的方式，在 GPU 層級處理資料。

不過，在許多情況下，「雖然有一些成本，但能運作」要比「完全不能運作」更好。因此，也會盡可能提供會發生 CPU copy 等操作的 fallback 機制。

如果成本變高，將以某種形式通知使用者。我們不會默默地把一架平台鋼琴放到使用者肩上，哪怕姿態再怎麼彬彬有禮。

4. 支援許多平台

IPC 通訊的價值，正是在於它能夠跨越各種應用程式的邊界。

為了提高使用者期待、擴大社群，並且——我們就坦率一點吧——也為了 SEO，本專案將毫不羞怯地公開許多模板式的、未經充分驗證的程式碼。

不過，為了不讓使用者真正陷入悲傷，文件中會認真註明「這可能無法運作」。

誠實很重要。尤其是在發布那些可能會禮貌地爆炸的程式碼時。

5. 透過 GitHub Actions 等工具通過 CI / Unit Test

為了圖個安心，也為了切實體會 CI 的困難。

實際上，即使 CI 變綠了，很多時候事情也完全沒有被正確實作。

AI agent 會很快寫出 CI 腳本。可是，它們也會很快滿足於「變綠了」這個結果。即使告訴它們要認真確認 CI 結果，它們也很快就會怠惰起來。

而且，CI 本身也常常沒有意義。

很辛苦。

但還是加油吧。

6. 為了讓寫程式變得有趣，也為了世界和平

「寫程式」這一行為本身，正在發生巨大的變化。

我也希望這個專案能夠被定位為一種訓練，以及面向這種變化的工作流程原型實驗的一部分。

也希望大家都能思考新時代的寫程式，並採取某種行動。

願你的 build 可以重現，願你的 agent 聽話，願你的世界大致和平。

2026/05/03
在讓 AI agent 處理另一項工作的空檔寫下。

2bit

</div>

<div class="about-lang-content" data-lang="ko" style="display:none" markdown="1">

nozzle에 대하여

이 라이브러리는 현재 사용할 수 있어 보이기 위해 최선을 다하고 있지만, 실제로는 아직 매우 불완전하다. 그러니 부디, 충분한 겸손을 담아 부탁드리건대, 화내지 말고 계속 읽어 주었으면 한다.

서문

AI agent가 등장한 지금, 누구나 라이브러리를 비교적 쉽게 수정시킬 수 있게 되었다.

“바퀴의 재발명”이라는 말의 의미도 조금은 달라지고 있는 듯하다.

그래서 이 라이브러리는, 일단 가능해 보이는 기능은 가능한 한 구현해 보려 한다. 그 기능이 필요한 사람은 한번 사용해 보고, 동작하지 않는다면 디버깅을 시키고, 리뷰를 시킨 뒤 PR을 보내 주었으면 한다. 물론, 적절한 품격을 갖추어서.

이를 위해 필요한 것은 과제와 설계 사상이다. 설계 자체는 이미 코드라는 형태로 공개되어 있다고 믿고 있다 — 명백히 디버깅이 부족해 보이는 코드이긴 하지만.

따라서 이 라이브러리는 과제와 설계 사상을 문서화하여 공개한다.
(W.I.P.)

과제와 설계 사상

이 프로젝트는 위대한 선구자인 Syphon과 Spout의 후계자를 목표로 기능을 구현한다.

1. 가능한 한 같은 코드로 크로스 플랫폼에서 다룰 수 있을 것

macOS에서도, Windows에서도, 그리고 Linux에서도 같은 코드로 사용할 수 있는 것을 목표로 한다.

지금까지의 문제였던:

“macOS에서는 Syphon, Windows에서는 Spout, 그럼 Linux에서는… 어떻게 하지?”

라는 상황을 해결하고자 한다.

고귀한 질문이다. 비극적인 질문이다. 그리고 이제는 가급적 그만 묻고 싶은 질문이다.

2. 가능한 한 많은 포맷을 지원할 것

float depth 데이터나 다양한 머신러닝 데이터를 다룰 수 있도록 float32, RG 컬러 등의 포맷을 지원하는 것을 목표로 한다.

다만 이는 최종 구현 프레임워크에도 의존하므로, “가능한 한”이라는 매우 책임감 있으면서도 상당히 애매한 조건을 붙이고 있다.

3. 가능한 한 효율적일 것

당연한 이야기지만, 큰 텍스처를 복사하는 비용은 무겁다.

이 부분은 Syphon과 Spout을 본받아, 가능한 한 zero-copy 방식으로 GPU 레벨에서 다루는 것을 목표로 한다.

다만 약간의 비용을 희생하더라도 “동작하지 않는 것”보다 “동작하는 것”이 나은 경우도 많다. 따라서 CPU copy 등이 발생하는 fallback도 가능한 한 제공한다.

비용이 커지는 경우에는 사용자에게 어떤 형태로든 알린다. 사용자 어깨 위에 그랜드 피아노를 조용히 올려놓는 일은 하지 않겠다. 아무리 공손하게 올려놓는다 해도 말이다.

4. 많은 플랫폼을 지원할 것

IPC 통신의 가치는 다양한 애플리케이션을 가로지를 수 있을 때 더욱 커진다.

사용자의 기대를 높이고, 커뮤니티를 키우며, 그리고 — 솔직히 말하자면 — SEO 대책을 위해서라도, 여러 템플릿 형태의 미검증 코드를 부끄러움 없이 공개한다.

다만 사용자를 진심으로 슬프게 만들지 않기 위해, “동작하지 않을 가능성이 있음”은 문서에 제대로 명시한다.

정직은 중요하다. 특히 예의 바르게 폭발할지도 모르는 코드를 배포할 때는 더욱 그렇다.

5. GitHub Actions 등으로 CI / Unit Test를 통과시킬 것

마음의 위안을 얻기 위해서, 그리고 CI가 얼마나 어려운지 실감하기 위해서.

실제로 CI가 초록색이 되어도, 전혀 제대로 구현되어 있지 않은 경우가 많다.

AI agent는 CI 스크립트를 금방 작성해 준다. 그러나 금방 초록색이 된 것에 만족한다. CI 결과를 제대로 확인하라고 해도 곧바로 게을러진다.

그리고 CI 자체가 무의미한 경우도 많다.

힘들다.

하지만 힘내자.

6. 코딩이 즐겁고 세계가 평화롭기 위해

코딩이라는 행위는 크게 변화하려 하고 있다.

이 프로젝트에도 그 변화를 위한 훈련과 워크플로 프로토타이핑의 일환이라는 위치를 부여하고 싶다.

여러분도 새로운 시대의 코딩에 대해 생각하고, 어떤 형태로든 행동을 시작해 주었으면 한다.

여러분의 빌드는 재현 가능하고, agent는 순종적이며, 세계는 적당히 평화롭기를.

2026/05/03
AI agent에게 다른 일을 맡겨 둔 틈새 시간에.

2bit

</div>

<div class="about-lang-content" data-lang="ru" style="display:none" markdown="1">

О nozzle

Эта библиотека сейчас изо всех сил старается выглядеть пригодной к использованию, хотя на самом деле она всё ещё глубоко неполна. Поэтому я со всей надлежащей скромностью прошу вас продолжить чтение и не сердиться.

Предисловие

Теперь, когда на сцене появились AI-агенты, практически любой человек может с относительной лёгкостью поручить им изменить библиотеку.

Мне кажется, что и смысл выражения «изобретать велосипед» тоже начал меняться.

Поэтому эта библиотека пока будет пытаться реализовывать все функции, которые выглядят осуществимыми. Те, кому такие функции нужны, могут попробовать ими воспользоваться; если они не работают, пожалуйста, заставьте их пройти отладку, ревью и отправьте PR. Разумеется, со всей надлежащей торжественностью.

Для этого нужны ясно сформулированные задачи и философия проектирования. Сам дизайн, как я полагаю, уже опубликован в виде кода — кода, которому, совершенно очевидно, всё ещё недостаёт отладки.

Поэтому эта библиотека будет документировать и публиковать свои задачи и философию проектирования.
(W.I.P.)

Задачи и философия проектирования

Этот проект стремится реализовать функциональность, достойную стать преемником великих первопроходцев Syphon и Spout.

1. Быть кроссплатформенной и использовать как можно больше общего кода

Цель состоит в том, чтобы библиотекой можно было пользоваться одним и тем же кодом на macOS, Windows и Linux.

Мы хотим решить давнюю проблему:

«На macOS у нас Syphon, на Windows Spout, а на Linux… ну и что же делать?»

Благородный вопрос. Трагический вопрос. Вопрос, который нам хотелось бы больше не задавать.

2. Поддерживать как можно больше форматов

Библиотека стремится поддерживать такие форматы, как float32 и цвет RG, чтобы работать с float-данными глубины и различными данными машинного обучения.

Однако это также зависит от финального фреймворка реализации, поэтому мы добавляем условие, одновременно ответственное и восхитительно расплывчатое: «насколько это возможно».

3. Быть как можно более эффективной

Это очевидно, но стоимость копирования больших текстур высока.

Следуя примеру Syphon и Spout, цель состоит в том, чтобы по возможности работать на уровне GPU и использовать zero-copy.

Однако во многих случаях «работает, пусть и с некоторыми затратами» лучше, чем «не работает вообще». Поэтому fallback-механизмы, включающие CPU copy и тому подобные вещи, также будут предоставляться настолько, насколько это возможно.

Если стоимость операции становится высокой, пользователь будет каким-либо образом уведомлён. Мы не будем молча класть ему на плечи рояль, даже если сделаем это с безупречной вежливостью.

4. Поддерживать множество платформ

Ценность IPC-коммуникации возрастает именно потому, что она позволяет пересекать границы между различными приложениями.

Чтобы повысить ожидания пользователей, расширить сообщество и — не будем стесняться — помочь SEO, проект будет без всякого смущения публиковать множество шаблонных фрагментов непроверенного кода.

Однако, чтобы не причинять пользователям настоящую печаль, в документации будет честно указано, если что-то может не работать.

Честность важна. Особенно когда распространяешь код, который может вежливо взорваться.

5. Прогонять CI / Unit Tests через GitHub Actions и подобные инструменты

Для душевного спокойствия, а также чтобы прочувствовать, насколько CI на самом деле сложна.

На практике даже зелёная CI вовсе не всегда означает, что всё действительно реализовано правильно.

AI-агенты быстро пишут CI-скрипты. Но они так же быстро удовлетворяются тем, что всё стало зелёным. Даже если сказать им внимательно проверить результаты CI, они вскоре начинают лениться.

Да и сама CI часто оказывается бессмысленной.

Это тяжело.

Но будем стараться.

6. Чтобы программирование было радостным, а мир — мирным

Сам акт программирования находится на пороге больших изменений.

Я также хочу, чтобы этот проект служил частью тренировки и прототипирования workflow для этой трансформации.

Надеюсь, вы тоже задумаетесь о программировании в новую эпоху и предпримете какие-либо действия.

Пусть ваши сборки будут воспроизводимыми, ваши агенты послушными, а ваш мир — в разумной степени мирным.

2026/05/03
В свободную минуту, пока AI-агент занимался другой задачей.

2bit

</div>

<script>
(function() {
  var btns = document.querySelectorAll('.lang-btn');
  var sections = document.querySelectorAll('.about-lang-content');
  var langMap = {
    'ja':'ja','en':'en','fr':'fr','de':'de','es':'es',
    'pt':'pt','pt-BR':'pt','it':'it',
    'zh':'zh-Hans','zh-CN':'zh-Hans','zh-Hans':'zh-Hans',
    'zh-TW':'zh-Hant','zh-Hant':'zh-Hant','zh-HK':'zh-Hant',
    'ko':'ko','ru':'ru'
  };

  function switchLang(lang) {
    btns.forEach(function(b){ b.classList.toggle('active', b.dataset.lang === lang); });
    sections.forEach(function(s){ s.style.display = s.dataset.lang === lang ? 'block' : 'none'; });
    try { localStorage.setItem('about-lang', lang); } catch(e) {}
  }

  var bl = navigator.language || '';
  var target = langMap[bl] || langMap[bl.split('-')[0]] || 'ja';
  var saved = null;
  try { saved = localStorage.getItem('about-lang'); } catch(e) {}
  switchLang(saved || target);

  btns.forEach(function(btn){
    btn.addEventListener('click', function(){ switchLang(btn.dataset.lang); });
  });
})();
</script>