-- Consulta para encontrar o relatório da cena do crime correspondente à data e local do crime
SELECT * FROM crime_scene_reports
WHERE date = '28 de Julho de 2020' AND location = 'Chamberlim Street';

-- Consulta para obter informações sobre os suspeitos associados ao relatório da cena do crime
SELECT * FROM suspects
WHERE report_id = 'ID_DO_RELATÓRIO';

-- Consulta para verificar os álibis dos suspeitos
SELECT * FROM alibis
WHERE suspect_id = 'ID_DO_SUSPEITO';

-- Consulta para analisar as conexões dos suspeitos com possíveis cúmplices
SELECT * FROM connections
WHERE suspect_id = 'ID_DO_SUSPEITO';

-- Consulta para encontrar pistas ou evidências que incriminem o(s) suspeito(s)
SELECT * FROM evidence
WHERE suspect_id = 'ID_DO_SUSPEITO';

INSERT INTO crime_scene_reports (date, location, description) VALUES ('DATA_DO_CRIME', 'LOCAL_DO_CRIME', 'DESCRICAO_DO_CRIME');

INSERT INTO suspects (name, report_id) VALUES ('NOME_DO_SUSPEITO', 'ID_DO_RELATORIO');

-- Inserir dados sobre os álibis dos suspeitos
INSERT INTO alibis (suspect_id, alibi_date, alibi_details) VALUES ('ID_DO_SUSPEITO', 'DATA_DO_ALIBI', 'DETALHES_DO_ALIBI');

-- Inserir dados sobre as conexões dos suspeitos com possíveis cúmplices
INSERT INTO connections (suspect_id, connection_type, connection_details) VALUES ('ID_DO_SUSPEITO', 'TIPO_DE_CONEXAO', 'DETALHES_DA_CONEXAO');

-- Inserir dados sobre as evidências que incriminam os suspeitos
INSERT INTO evidence (suspect_id, evidence_details) VALUES ('ID_DO_SUSPEITO', 'DETALHES_DA_EVIDENCIA');

