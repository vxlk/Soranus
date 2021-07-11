from ftx_api import *
ws_start_all()
tickers = ws_open_tickers()
while (True):
    for ticker in tickers:
        print("ticker from test:")
        print(ws_ticker_price(ticker))