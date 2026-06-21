# Projekt-Fahrplan — Schritt für Schritt durch die Gates

> **Allgemeine** Arbeitsgrundlage für ein ET/DV-Abschlussprojekt vom Typ „Machbarkeitsstudie mit vier Gates".
> Themenunabhängig: Egal worum es geht — du erkennst zu Projektbeginn die tatsächlichen Aufgaben und wendest den passenden Baustein an.
> Gegliedert nach **Gates**, nicht nach Tagen (die Abgabezeitpunkte können variieren). Mitgebrachte Vorlagen/Code sind erlaubt.

---

## 0. Worauf es ankommt (Grundprinzipien)

- **Aufgaben erkennen, Baustein anwenden** — egal welches Thema: zuerst die konkreten Aufgaben herauslesen, dann den passenden vorbereiteten Baustein einsetzen.
- **Verdeckte Anforderungen zuerst** — die versteckten Punkte erkennen und absichern; dort entscheiden sich die Bewertungen.
- **Ein roter Faden** über alle Gates: **Problem → Lösung → Machbarkeit → Wirtschaftlichkeit → Empfehlung.**
- **Modular & alles festhalten** — Lösungen modular und weiterentwickelbar (wird bewertet); jede Entscheidung dokumentieren. Die spätere Doku darf kein neues Material enthalten.

### Das immer gleiche Muster
Ein Unternehmen will etwas ändern/investieren, hat Qualitäts- und Kostendruck und braucht eine Entscheidung:
*technisch und wirtschaftlich machbar — und soll man es so tun?*

### Erste Schritte zu Projektbeginn
1. **Briefing & alle Anlagen vollständig lesen** → zwei Listen: *explizite* und *verdeckte* Anforderungen.
2. **Konkrete Aufgaben identifizieren** und den jeweils passenden Baustein aus Gate 2 zuordnen.
3. **Verdeckte Anforderungen jagen** — sie stecken zuverlässig in:
   - rhetorischen Fragen des Auftraggebers („Ob sich das lohnt?", „Was, wenn das ausfällt?"),
   - Nebensätzen mit Konsequenz (ein Schritt entfällt oder kommt hinzu),
   - Normverweisen (z. B. ISO 9001 → Qualitätsregelkreis schließen),
   - Zukunftsandeutungen („später mehr…", „weitere…") → Skalierbarkeit mitdenken.
4. **Anforderungen auf die Gates verteilen** und eine **Annahmen-Liste** starten (wird in Gate 3 gefordert).

> **Wichtigste Regel:** Während der gesamten Bearbeitung alles festhalten. In der Dokumentationsphase nur noch ausformulieren.

---

## 1. Die vier Gates im Überblick

| Gate | Inhalt | Ziel |
|---|---|---|
| **Gate 1 — Projektsteckbrief** | Ausgangslage, Anforderungen, Ziele, ZKQ, Abgrenzungen, Meilensteine, Beteiligte | Scope & Auftrag klären |
| **Gate 2 — Technologische Machbarkeit** | je technische Teilaufgabe: Steuerung, Hardware, Regelung, Datenerfassung, Datenbank, Auswertung, Qualität | Belegen, dass jede Teillösung funktioniert |
| **Gate 3 — Entscheidungsvorlage** | PSP, Planung, Kosten, Wirtschaftlichkeit, Risiken/Chancen, Empfehlung | Projektmäßige Machbarkeit + Empfehlung (**als PDF**) |
| **Gate 4 — Präsentation** | Projektverlauf + Ergebnisse (15–20 min) | Überzeugend zeigen |

Reihenfolge und Aufbau sind in jedem Projekt gleich — nur die Inhalte wechseln. Der **Zeitpunkt** der Abgaben steht nicht fest.

---

## 2. Schritt für Schritt durch die Gates

> ⚠ markiert die typischen Stolperstellen (verdeckte Anforderungen). Bausteine mit *(falls vorhanden)* nur anwenden, wenn dein Projekt die Aufgabe enthält.

### Gate 1 — Projektsteckbrief
*Ziel: Scope, Ziele und Auftrag klar festlegen. Die Vorlage „Projektsteckbrief" ausfüllen.*

1. **Projekttitel** festlegen — kurz und treffend.
2. **Ausgangslage** beschreiben: Unternehmen, Marktumfeld, Anlass der Änderung/Investition, aktueller Prozess und Eingriffsstelle.
3. **Anforderungen** aus der Startliste vollständig übernehmen — explizit *und* verdeckt.
4. **Projektziele** formulieren — Machbarkeit nachweisen, Wirtschaftlichkeit bestimmen, Qualität/Prozess verbessern.
5. **ZKQ-Vorgaben** festlegen (Zeit / Kosten / Qualität) — jeweils **messbar** (eine Zahl, eine Frist, ein Schwellwert).
   - ⚠ Vage Ziele kosten Punkte.
6. **Abgrenzungen** setzen — was ausdrücklich *nicht* zum Projekt gehört (z. B. nur Machbarkeitsnachweis statt Serienreife).
7. **Meilensteine / wichtige Termine** — die vier Gates.
8. **Beteiligte** laut Vorlage eintragen: Auftraggeber, Projektleitung, Projektmitglieder, Lenkungsausschuss; Datum/Unterschrift.

**Hilfsmittel:** vorausgefüllter Gate-1-Master · Anforderungs-Hilfe.

### Gate 2 — Technologische Machbarkeit
*Ziel: für jede technische Teilaufgabe belegen, dass sie funktioniert. Keine Vorlage → je Lösung selbst strukturieren.*

Für **jede** Teilaufgabe immer dieselbe Schleife durchlaufen:
**Anforderung klären → Lösung entwerfen → Prototyp/Umsetzung → Testen → Machbarkeit dokumentieren.**
Danach die zutreffenden Bausteine wählen:

1. **System verstehen & abbilden.** Gesamtablauf/-aufbau darstellen, betroffene Stelle und alle Schnittstellen markieren (Flussdiagramm/PAP).

2. **Steuerung / Automatisierung** *(falls SPS / IEC 61131-3)*
   - Vorgegebene I/O-Liste übernehmen; Sensoren als **Öffner/Schließer** kennzeichnen.
   - Ablauf als **Schrittkette** (Schritt/Transition) entwerfen und als Ablaufdiagramm dokumentieren.
   - Sicherheit zuerst: Not-Aus/Schutz → definierter **sicherer Zustand**; danach Betriebsarten (EIN/AUS, Start/Stopp).
   - Varianten/Verzweigungen abbilden (unterschiedliche Werkstücke, Modi, Stückzahlen); umsetzen und simulieren.
   - ⚠ Öffner invertiert auswerten · alle geforderten Varianten/Verriegelungen · sicheren Zustand bei Stopp/Störung definieren.

3. **Hardware auswählen & Beschaffung vorbereiten** *(falls gefordert)*
   - Bedarf quantifizieren (z. B. Anzahl Ein-/Ausgänge, Leistung, Schnittstellen) — mit Reserve.
   - Geeignete Komponente auswählen, Beschaffung vorbereiten (Stückliste + Preise).
   - Kosten an die Gate-3-Kostenabschätzung übergeben.
   - ⚠ Reserven einplanen · keinen Bedarf (z. B. Schutz-/Statuskanäle) übersehen.

4. **Regelung** *(falls Regelstrecke)*
   - Strecke aus der gegebenen Sprungantwort identifizieren (Kennwerte, z. B. Verzugszeit Tu / Ausgleichszeit Tg).
   - Reglertyp wählen (P/PI/PID), Parameter nach Standardverfahren (z. B. Ziegler-Nichols, Chien-Hrones-Reswick).
   - Regelkreis simulieren und gegen die Vorgabe prüfen (Sollwert, erlaubte Toleranz, geforderte Schnelligkeit).
   - ⚠ Erlaubte Toleranz nutzen · Reglerwahl begründen · Kennwerte sauber ablesen.

5. **Datenerfassung / Programmierung** *(falls Programm / Schnittstelle)*
   - Datenmodell festlegen (geforderte Felder + Datentypen), modular umsetzen (`struct` / getrennte Module).
   - **Schnittstelle als Vertrag** definieren — Format, Reihenfolge, Trennzeichen, Encoding, Zahlen-/Datumsformat.
   - Funktion mit Testdaten prüfen.
   - ⚠ Schnittstelle eindeutig · Datentypen sauber · erweiterbar halten.

6. **Datenbank** *(falls Datenhaltung)*
   - ER-Schema entwerfen, normalisieren, Schlüssel festlegen.
   - Anlegen, **Import testen**, Testdatensätze, Abfragen für die Auswertung.
   - Skalierbarkeit andiskutieren (mehr Felder, Aufteilung in mehrere Datenbanken).
   - ⚠ Import nicht nur behaupten, sondern testen · Skalierbarkeit erwähnen.

7. **Auswertung / Visualisierung** *(falls Anzeige / Statistik)*
   - **Exakt die geforderten Kennzahlen** (z. B. Mittelwert/Standardabweichung), den geforderten Schwellwert und die geforderte Stichprobengröße (z. B. die letzten N Datensätze) umsetzen.
   - Passende Diagramme; Schwelle und Stichprobengröße parametrierbar; ggf. Zeitverlauf und automatische Aktualisierung (Timer).
   - Umsetzung in Qt / C++ (Datenzugriff über QtSql oder die DB-C-API); pro Anzeige/Station wiederverwendbar.
   - ⚠ Exakte Spezifikation treffen (Kennzahl/Schwelle/Anzahl) · Zeitverlauf statt nur Momentaufnahme.

8. **Qualität / Qualitätsmanagement** *(falls Fehler-/Reklamationsdaten oder Normbezug)*
   - Daten nach Ursache kategorisieren; **Pareto** (Häufigkeit) *und* Schweregrad → die schwerwiegendsten bestimmen.
   - Ursachen ermitteln (Ishikawa, 5-Why) und mit den technischen Lösungen **verknüpfen**; Kennzahlen wählen.
   - Bei Normbezug (z. B. ISO 9001) den Regelkreis schließen: Messen → Auswerten → Maßnahmen → Wirkung.
   - ⚠ Ursachen mit konkreten Lösungen verknüpfen · die schwerwiegendsten, nicht nur die häufigsten, bestimmen.

9. **Modularität & Nachhaltigkeit dokumentieren** — modularer, weiterentwickelbarer Aufbau und Ressourceneffizienz. Wird ausdrücklich bewertet.

**Hilfsmittel:** Schrittketten-Gerüst (CODESYS) · Reglerentwurf-Skript · Datenimport-Gerüst (CSV→DB) · DB-architect (ER, PAP) · Qt-Visu-Gerüst · Pareto-/Ishikawa-Vorlage.

### Gate 3 — Entscheidungsvorlage *(als PDF abzugeben)*
*Ziel: projektmäßige Machbarkeit zeigen und eine Empfehlung aussprechen.*

1. **Stammdaten:** Projektbezeichnung, Ausgangslage, Projektziele, Abgrenzungen, projektbearbeitende Personen.
2. **Inhaltliche Umsetzung:** Was wird wie (Maschinen, Methoden, Verfahren) gemacht — technologische Meilensteine aus dem PSP.
3. **Projektplanung:**
   - Projektstrukturplan (Teilprojekte → Arbeitspakete).
   - Gantt-/Zeitplanung, Meilensteine, Ressourcen.
   - Notizen zu getroffenen Annahmen.
4. **Kostenabschätzung je Sammelvorgang:** Personal gemäß Gantt + Anlagen/Maschinen + Material + Gemeinkosten.
5. **Wirtschaftlichkeit** — Varianten vergleichen und Amortisation/Break-even bestimmen.

   *Allgemeines Rechenschema (Werte aus dem konkreten Briefing einsetzen):*
   - Investition = Summe einmaliger Kosten (Anschaffung + Inbetriebnahme + Software …); dazu laufende Kosten/Jahr.
   - Stückkosten je Variante = Material + (Bearbeitungszeit × Lohnsatz) + anteilige Anlagen-/Wartungskosten.
   - Einsparung pro Stück = Differenz der Varianten — **indirekte Effekte** (entfallende/zusätzliche Schritte) einrechnen.
   - Break-even-Menge = Investition / Einsparung pro Stück → gegen reale Kapazität/Bedarf einordnen.
   - ⚠ Indirekte Effekte einrechnen · Ergebnis einordnen (lohnt es sich bei der realen Stückzahl?), nicht nur die Zahl nennen.
6. **Projektrisiken:** identifizieren, bewerten (Eintritt × Auswirkung, mit Begründung), Gegenmaßnahmen.
   - ⚠ Ausfall einer kritischen Einzelressource (Single Point of Failure) mit Gegenmaßnahme behandeln — danach fragt der Auftraggeber gern indirekt.
7. **Projektchancen:** Nutzen der Umsetzung (Kosten, Qualität, eigene Kontrolle, Skalierbarkeit, Nachhaltigkeit).
8. **Empfehlung** an den Lenkungsausschuss — eine klare, begründete Aussage (Ja/Nein + Bedingungen); Datum/Unterschrift; als PDF exportieren.
   - ⚠ „Sowohl-als-auch" ohne klare Empfehlung kostet Punkte.

**Hilfsmittel:** Gate-3-Master · DB-architect (PSP) · Risikomatrix · Wirtschaftlichkeits-/Break-even-Rechner.

### Gate 4 — Präsentation
*Ziel: Projektverlauf und Ergebnisse überzeugend zeigen (15–20 min).*

1. **Foliendramaturgie:** Ausgangslage/Problem → Ziele & ZKQ → Vorgehen → technologische Machbarkeit (je Teillösung) → Wirtschaftlichkeit → Risiken & Chancen → Empfehlung.
2. **Live-Demo** vorbereiten — die zentralen Ergebnisse vorführbar machen (z. B. Simulation und Auswertungs-Anzeige).
3. **Roter Faden prüfen** — Problem ↔ Lösung ↔ Daten ↔ Wirtschaftlichkeit sichtbar machen.
4. **Proben & Timing** — Sprecherübergänge, Zeitrahmen 15–20 min, mögliche Fragen antizipieren.

**Hilfsmittel:** Präsentations-Template.

---

## 3. Vorbereitete Hilfsmittel

| Baustein | Unterstützt | Status |
|---|---|---|
| Anforderungs-Hilfe (erkennt verdeckte Anforderungen) | Projektstart | geplant |
| Gate-1- & Gate-3-Master (vorausgefüllt) | Gate 1, Gate 3 | geplant |
| PSP / Gantt / Risikomatrix / Kostentabelle | Gate 3 | teils ✔ (DB-architect: PSP) |
| Wirtschaftlichkeits- / Break-even-Rechner | Gate 3 | geplant |
| Pareto- / Ishikawa-Vorlage | Gate 2 (Qualität) | teils ✔ (DB-architect: Mindmap) |
| Schrittketten-Gerüst (CODESYS, generisch) | Gate 2 (Steuerung) | geplant |
| Reglerentwurf-Skript (Sprungantwort → PID) | Gate 2 (Regelung) | geplant |
| Datenimport-Gerüst (CSV → Datenbank) | Gate 2 (Daten) | **fertig ✔** |
| DB-Schema / ERM + Import (DB-architect) | Gate 2 (DB) | **fertig ✔** |
| PAP / Flussdiagramm / UML (DB-architect) | Gate 2, Doku | **fertig ✔** |
| Qt-/C++-Visu-Gerüst (QtSql oder DB-C-API, Qt Charts) | Gate 2 (Auswertung) | geplant |
| Präsentations-Template | Gate 4 | geplant |

**DB-architect** (eigenes Tool) deckt die Diagramm-Seite themenunabhängig ab: ER-Diagramme, PSP, PAP, UML, Mindmaps — Export PNG/PDF.
Nicht abgedeckt: echte Datenauswertung/Statistik, Kostenrechnung, SPS-Code, Reglerauslegung, lauffähige Programme.

---

## 4. Dokumentations-Phase

- **Regel:** nur Material aus den Gates + Präsentation — nichts Neues. Deshalb während der Bearbeitung lückenlos erfassen.
- **Capture je Arbeitspaket:** Ziel, Vorgehen, Screenshots, Rechenweg, Ergebnis, Entscheidung, Annahmen, offene Punkte.
- **Doku-Struktur** (an Gates ausgerichtet): Ausgangslage → Anforderungen → Vorgehen/Planung → technologische Machbarkeit (je Teillösung) → Wirtschaftlichkeit → Qualität/Risiken/Chancen → Empfehlung/Fazit → Anhang.

---

## 5. Prüfpunkte: verdeckte Anforderungen (vor jeder Abgabe)

- [ ] Jede rhetorische Auftraggeber-Frage beantwortet?
- [ ] Indirekte Kosteneffekte berücksichtigt (entfallende/zusätzliche Schritte)?
- [ ] Break-even / Amortisation gegen reale Kapazität bzw. Bedarf eingeordnet?
- [ ] Single-Point-of-Failure-Risiko mit Gegenmaßnahme behandelt?
- [ ] Benötigte Hardware bestimmt & Beschaffung vorbereitet (Bedarf gezählt)?
- [ ] Sensorlogik (Öffner/Schließer) bzw. Sonderfälle korrekt behandelt?
- [ ] Alle geforderten Varianten / Verzweigungen abgebildet?
- [ ] Schnittstellen (Datei/Format) als Vertrag definiert?
- [ ] Exakte geforderte Kennzahlen / Schwellen / Stichprobengröße getroffen?
- [ ] Skalierbarkeit / Erweiterbarkeit erwähnt?
- [ ] Roter Faden Problem ↔ Lösung ↔ Daten ↔ Wirtschaftlichkeit sichtbar?
- [ ] ZKQ-Ziele messbar formuliert?
- [ ] Modularität / Nachhaltigkeit adressiert & Annahmen-Liste gepflegt?
- [ ] Alles für die Dokumentationsphase festgehalten?
