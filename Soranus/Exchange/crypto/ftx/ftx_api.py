from ftx_websocket.client import FtxWebsocketClient
# from ftx_rest.client import FtxClient
import threading
import os

api_key = os.environ.get('FTX_API_KEY')
api_secret = os.environ.get('FTX_API_SECRET')

# Websocket Container Class
class ws_api_impl():
    def __init__(self):
        self.ticker_data = {}
        self.open_tickers = []
        self.ticker_threads = {}

        #setup client
        self.client = FtxWebsocketClient()
        self.client._api_key = api_key
        self.client._api_secret = api_secret
        self.client.connect()

    def current_price(self, ticker : str) -> float:
        if not ticker in self.ticker_data.keys():
            ws_start(ticker)
        self.ticker_data[ticker] = "None" # initial value
        return self.ticker_data[ticker]

    def __ws_ticker_get_func__(self, ticker : str) -> None:
        while(True):
            self.ticker_data[ticker] = self.client.get_ticker(market=ticker)
            print("ticker func:")
            print(self.client.get_ticker(market=ticker))

# REST Container Class
class rest_api_impl():
    def __init__(self):
        pass

ws_api = ws_api_impl()
rest_api = rest_api_impl()

# ------ WEBSOCKET API ------#
def ws_start(market : str) -> None:
    # start thread
    # while (connection):
    # get ticker
    ws_api.ticker_threads[market] = threading.Thread(target=ws_api.__ws_ticker_get_func__, args=(market,))
    ws_api.ticker_threads[market].start()
    ws_api.open_tickers.append(market)

def ws_open_tickers() -> list:
    return ws_api.open_tickers

def ws_start_all() -> None:
    ticker_list = ['SOL/USD']
    for ticker in ticker_list:
        ws_start(ticker)

def ws_ticker_price(ticker : str) -> float:
    return ws_api.current_price(ticker)
# ------ WEBSOCKET API ------#

# ------ REST API ------#
# ------ REST API ------#