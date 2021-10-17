import express from "express"

export default class ResponseBuilder {

    private _servers: any
    private _response: any

    constructor(options: any, req: express.Request,) {
        this._servers = options
        const server = this.findServer(req.hostname)
        this._response = this.findEndpoint(server, req.url, req.method)
    }

    private findServer(name: string) {
        for (const server of this._servers) {
            if (server.hostname == name)
                return server
        }
    }

    private findEndpoint(server: any, url: string, method: string) {
        for (const e of server.endpoints) {
            const reg = new RegExp('^' + e.path + '$')
            if (e.method === method && reg.test(url)) {
                return e.response
            }
        }
    }

    private setHeader(res: express.Response) {
        for (const h of this._response.headers) {
            res.setHeader(h.name, h.value)
        }
    }

    end(res: express.Response) {
        this.setHeader(res)
        res.status(this._response.statusCode).end(this._response.body)
    }
}